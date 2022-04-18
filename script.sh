#!/bin/bash

# get pid:
#'lsof -p $$ -a -d 0-256'
#'ps | tail -1 | cut -d " " -f1'

RED='\033[0;31m'
CYAN='\033[0;36m'
GREEN='\033[0;32m'
DEFAULT='\033[0m'

make | grep -v "make: Nothing"

mkdir dir
rm -f log

EXIT_CODES=false
SHOW_CMD=true
FD=true

test()
{
	for CMD in "$@" ; do	
		if [ "$SHOW_CMD" = true ] ; then
			echo -ne "$CYAN$CMD: $DEFAULT"
		fi
		echo $CMD >> dir/infile
	done

	if [ "$EXIT_CODES" = true ] ; then
		echo 'echo $?' >> dir/infile
	fi

	< dir/infile ./minishell > dir/minishell_out 2> dir/minishell_error
	STATUS=$?

	if grep -q "minishell" dir/minishell_error ; then
		cut -d ' ' -f 2- dir/minishell_error > dir/tmp2
		cat dir/tmp2 > dir/minishell_error
	fi

	if grep -q "line " dir/minishell_error ; then
		cut -d ' ' -f 3- dir/minishell_error > dir/tmp2
		cat dir/tmp2 > dir/minishell_error
	fi

	echo 'set +e' | cat - dir/infile > dir/tmp3
	cat dir/tmp3 > dir/infile

	< dir/infile bash > dir/bash_out 2> dir/bash_error
	STATUS=$?

	if grep -q "bash" dir/bash_error ; then
		cut -d ' ' -f 2- dir/bash_error > dir/tmp1
		cat dir/tmp1 > dir/bash_error
	fi

	if grep -q "line " dir/bash_error ; then
		cut -d ' ' -f 3- dir/bash_error > dir/tmp1
		cat dir/tmp1 > dir/bash_error
	fi

	diff dir/bash_out dir/minishell_out | tail -n +2 | grep -e "< " -e "> " >> dir/tmp
	diff dir/bash_error dir/minishell_error | tail -n +2 | grep -e "< " -e "> " >> dir/tmp

	if head -1 dir/tmp | grep -q "syntax error" ; then
		sed -in '1,2d' dir/tmp
		if grep -q "syntax error" dir/tmp ; then
			rm dir/tmp
		fi
	fi

	if [ -s dir/tmp ] ; then
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

echo
echo -e "$CYAN--- echo test suite ---$DEFAULT"
# Echo tests
test 'ech'
test 'echo'
test 'echo -n'
test 'echo $PWD'
test 'echo $NONEXISTING'
test 'echo a b c'
test 'echo a b	c'
test 'echo forrest'
test 'echo - a'
test 'echo --n a'
test 'echo n- a'
test 'echo n a'
test 'echo -nABC'
test 'echo -n -n'
#test 'echo -nn' bash is stupid
test 'ls | echo a b'
test 'ls | echo'
test 'ls | echo -n'

echo -e "$CYAN--- cd test suite ---$DEFAULT"
# cd tests
test 'c'
test 'cd /'
test 'cd $HOME' 'cd '
test 'cd nonexistent_dir'
test 'cd cd cd'
test 'cd src/ ..'
test 'cd pwd'

echo
echo -e "$CYAN--- pwd test suite ---$DEFAULT"
# Pwd tests
test 'pw'
test 'pwd'
test 'unset PWD' 'pwd'
test '/pwd'
test 'pwd' 'cd ..' 'pwd'

echo
echo -e "$CYAN--- export test suite ---$DEFAULT"
# Pwd tests
test 'expor'
test 'export variable=1' 'env | grep variable'
test 'export variable1=y variable2=x' 'env | grep -e variable1 -e variable2'
test 'export v_ariable=4'
test 'export _v_ariable=4'
test 'export variable='
test 'export ='
test 'export =hey'

echo
echo -e "$CYAN--- unset test suite ---$DEFAULT"
# Pwd tests
test 'unse PWD' 'echo $PWD'
test 'unset'
test 'unset PWD' 'echo $PWD'

echo
echo -e "$CYAN--- Lexer test suite ---$DEFAULT"
# Lexer tests
test ''	
test ' '	#space
test '	'	#tab
test ' 	 '	#mixed
test 'echo "''" "''" "a" "$" "$"'
test 'echo -$PWD$?$PATH-'
test 'echo -$a$.$PW$SHLVL"$P"WD'
test 'ls -a | echo -n'
test 'cat -e cat -e cat -e cat -e cat -e cat -e'
test 'cat cat cat cat cat cat cat'
test 'no_command'
test 'echo ""'
test 'echo <<>><>|$|	'

echo
echo -e "$CYAN--- General commands test suite ---$DEFAULT"
# commands (PATH)
test 'ls'
test 'ls -a'
test 'ls not_a_dir'
test 'cat Makefile minishell'
test 'not_a_command'
test 'git log --pretty="format:%H"'
test 'bash'
test 'sh'

echo
echo -e "$CYAN---Exit commands test suite...$DEFAULT"
test 'exit 42'
test 'exit 42 53 68'
test 'exit 259'
test 'exit 9223372036854775807'
test 'exit -4'
test 'exit wrong'
test 'exit wrong_command'
test 'exit a 3'
test 'exit -a 3'

#test '.'	error diff
test '/'
test './minishell'

# commands (absolute path)
test '/bin/bash'
test '/usr/bin/git status'

#redirects
test 'ls > dir/outfile'
test 'ls>dir/outfile'
test '> dir/outfile'
test '< dir/outfile'

# pipes
test '|' 'echo hey'
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

test 'echo "./minishell" | ./minishell'

echo
echo -e "$CYAN---Multiline commands test suite...$DEFAULT"

test 'echo $PWD' 'unset PWD' 'echo $PWD'
test '<< x cat' 'hey' 'x'
test 'echo "#!/bin/bash
/bin/ls" >> dir/infile2' 'chmod +x dir/infile2' './dir/infile2' 'rm dir/infile2'

echo -e "$CYAN---Finished$DEFAULT"

rmdir dir