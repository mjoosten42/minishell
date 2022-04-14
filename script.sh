#!/bin/bash

#lsof -p $$ -a -d 0-256

RED='\033[0;31m'
CYAN='\033[0;36m'
GREEN='\033[0;32m'
DEFAULT='\033[0m'

make | grep -v "make: Nothing"

mkdir dir
rm -f log

test()
{
	echo -ne $CYAN [$1]: $2 $DEFAULT

	echo $1 | bash > dir/bash_out 2> dir/tmp
	STATUS=$?
	#Bash gives line number with certain errors: we cut those
	if grep -q "line " dir/tmp
	then
		cut -d ' ' -f 4- dir/tmp > dir/bash_error
	else
		cut -d ' ' -f 2- dir/tmp > dir/bash_error
	fi
	echo "exit code: $STATUS" >> dir/bash_out

	rm -f dir/tmp

	echo $1 | ./minishell > dir/minishell_out 2> dir/tmp
	STATUS=$?
	if ! grep -q "line " dir/tmp
	then
		cut -d ' ' -f 2- dir/tmp > dir/minishell_error
	fi
	echo "exit code: $STATUS" >> dir/minishell_out

	rm -f dir/tmp

	diff dir/bash_out dir/minishell_out | tail -n +2 | grep -e "< " -e "> " >> dir/tmp
	diff dir/bash_error dir/minishell_error | tail -n +2 | grep -e "< " -e "> " >> dir/tmp
	
	if head -1 dir/tmp | grep -q "syntax error"
	then
		sed -i '' '1,2d' dir/tmp
		if grep -q "syntax error" dir/tmp
		then
			rm dir/tmp
		fi
	fi

	if [ -s dir/tmp ]
	then
		echo $1 >> log
		cat dir/tmp >> log
		echo -e $RED[KO] $DEFAULT
		cat < dir/tmp
	else
		echo -e $GREEN[OK] $DEFAULT
	fi

	rm dir/*
}

echo -e "$CYAN---Starting tests...$DEFAULT"
echo

echo -e "$CYAN---CD test suite...$DEFAULT"
# cd tests
test 'cd'
test 'cd /'
test 'cd $HOME'
test 'cd nonexistent_dir'
test 'cd cd cd'

echo
echo -e "$CYAN---Echo test suite...$DEFAULT"
# Echo tests
test 'echo'
test 'echo -n'
test 'echo $PWD'
test 'echo forrest'
test 'echo - a'
test 'echo --n a'
test 'echo n- a'
test 'echo n a'

echo
echo -e "$CYAN---PWD test suite...$DEFAULT"
# Pwd tests
test 'pwd'

echo
echo -e "$CYAN---Lexer test suite...$DEFAULT"
# Lexer tests
test 'echo "''" "''" "a" "$" "$"'
test 'ls -a | echo -n'
test 'cat -e cat -e cat -e cat -e cat -e cat -e'
test 'cat cat cat cat cat cat cat'
test 'no_command'
test '$PWD'

echo
echo -e "$CYAN---Basic test suite...$DEFAULT"
# basic tests
test ''	
test ' '	#space
test '	'	#tab
test ' 	 '	#mixed

echo
echo -e "$CYAN---General commands test suite...$DEFAULT"
# commands (PATH)
test 'ls'
test 'ls -a'
test 'ls not_a_dir'
test 'cat Makefile minishell'
test 'not_a_command'
test 'git log --pretty="format:%H"'
test 'bash'
test 'sh'
test 'ps | tail -1 | cut -d ' ' -f1'

echo
echo -e "$CYAN---Misc commands test suite...$DEFAULT"
test 'exit 42'
test 'exit 42 53 68'
test 'exit 259'
test 'exit 9223372036854775807'
test 'exit -4'
test 'exit wrong'
test 'exit wrong_command'
test 'exit a 3'
test 'exit -a 3'

test '.'
test './minishell'

# commands (absolute path)
test '/bin/bash'
test '/usr/bin/git status'

# custom binary
test './file' "#file doesn't exist"
echo '#!/bin/bash
ls' > file
test './file' "# no exec permission"
chmod a+x file
test './file' "# ls"
rm file

test 'type -a kill'

#redirects
test 'ls > dir/outfile'
test 'ls>dir/outfile'
test '> dir/outfile'
test '< dir/outfile'

# pipes
test '|'
test 'ls |'
test 'ls|'
test ' |'
test '| ls'
test 'ls | cat'
test 'ls|cat'
test '||'
test '| |'

# pipes combined with redirects
test '< Makefile cat | xargs > dir/outfile'
test 'cat<Makefile|>dir/outfile xargs'
test '<Makefile|>dir/outfile'
#test 'sleep 1 | ls test'	subject requires most _recent_ exit code

echo -e "$CYAN---Finished$DEFAULT"

rmdir dir