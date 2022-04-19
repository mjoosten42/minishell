#!/bin/bash

EXIT_CODES=true
SHOW_CMD=true
FD=true
MANUAL=false

RED='\033[0;31m'
CYAN='\033[0;36m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
DEFAULT='\033[0m'

make | grep -v "make: Nothing"

mkdir dir
rm -f log

test()
{
	for CMD in "$@" ; do	
		if [ "$SHOW_CMD" = true ] ; then
			echo -ne "$CYAN$CMD: $DEFAULT"
		fi
		echo $CMD >> dir/infile
	done

	if [ "$EXIT_CODES" = true ] ; then
		echo 'echo exit code: $?' >> dir/infile
	fi

	if [ "$FD" = true ] ; then
		echo "lsof -p \$\$ -a -d 0-256 | tail -n +2 | awk '{print \$4}'" >> dir/infile
	fi

	< dir/infile ./minishell > dir/minishell_out 2> dir/minishell_error

	if grep -q "minishell" dir/minishell_error ; then
		cut -d ' ' -f 2- dir/minishell_error > dir/tmp2
		cat dir/tmp2 > dir/minishell_error
	fi

	if grep -q "line " dir/minishell_error ; then
		cut -d ' ' -f 3- dir/minishell_error > dir/tmp2
		cat dir/tmp2 > dir/minishell_error
	fi

	< dir/infile bash > dir/bash_out 2> dir/bash_error

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

	if grep "syntax error" dir/tmp ; then
		cat dir/tmp
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

echo -e "$YELLOW--- echo test suite ---$DEFAULT"
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
test 'echo a     b'
test 'echo "a    b"'
#test 'echo -nn' bash is stupid
test 'ls | echo a b'
test 'ls | echo'
test 'ls | echo -n'

echo -e "$YELLOW--- cd test suite ---$DEFAULT"
# cd tests
test 'c'
test 'cd /'
test 'cd $HOME' 'cd ..'
test 'cd nonexistent_dir'
test 'cd cd cd'
test 'cd src/ ..'
test 'cd pwd'

echo
echo -e "$YELLOW--- pwd test suite ---$DEFAULT"
# Pwd tests
test 'pw'
test 'pwd'
test 'unset PWD' 'pwd'
test '/pwd'
test 'pwd' 'cd ..' 'pwd'

echo
echo -e "$YELLOW--- export test suite ---$DEFAULT"
# Pwd tests
test 'expor'
test 'export variable=1' 'env | grep variable'
test 'export variable1=y variable2=x' 'env | grep -e variable1 -e variable2'
test 'export v_ariable=4'
test 'export _v_ariable=4'
test 'export variable='
test 'export ='
test 'export =hey'
test 'export variable1=y 6variable=3 variable7=hey vari5albe=wrong'

echo
echo -e "$YELLOW--- unset test suite ---$DEFAULT"
# Pwd tests
test 'unse PWD' 'echo $PWD'
test 'unset'
test 'echo $PWD' 'unset PWD' 'echo $PWD'

echo
echo -e "$YELLOW--- exit commands test suite...$DEFAULT"
test 'exit 42'
test 'exit 42 53 68'
test 'exit 259'
test 'exit 9223372036854775807'
test 'exit -4'
test 'exit wrong'
test 'exit wrong_command'
test 'exit a 3'
test 'exit -a 3'

echo
echo -e "$YELLOW--- env commands test suite...$DEFAULT"
test 'en'
test 'env | grep PWD'
test 'env | grep PWD' 'unset PWD' 'env | grep PWD'

echo
echo -e "$YELLOW--- Lexer test suite ---$DEFAULT"
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
echo -e "$YELLOW--- General commands test suite ---$DEFAULT"
# commands (PATH)
test 'ls'
test 'ls -a'
test 'ls not_a_dir'
test 'cat Makefile minishell'
test 'not_a_command'
test 'git log --pretty="format:%H"'
test 'bash -c exit'
test 'sh -c exit'

#test '.'	error diff
test '/'

# commands (absolute path)
test '/bin/bash'
test '/usr/bin/git status'

#redirects
test 'ls > dir/outfile'
test 'ls>dir/outfile'
test '> dir/outfile'
test '< dir/outfile'

# pipes
test '|'
test 'ls |'
test 'ls|'
test '| ls |'
test ' |'
test '| ls'
test 'ls | cat'
test 'ls|cat'
test '||'
test '| |'
test '| | ls'
test 'ls | | cat'
test 'ls > test_log | cat'
test '> log | cat'
test '< | >'

# pipes combined with redirects
test '< Makefile cat | xargs > dir/outfile'
test 'cat<Makefile|>dir/outfile xargs'
test '<Makefile|>dir/outfile'
#test 'sleep 1 | ls test'	subject requires most _recent_ exit code

test 'echo "./minishell" | ./minishell'

echo
echo -e "$YELLOW---Multiline commands test suite...$DEFAULT"

test '<< x cat' 'hey' 'x'
test 'echo "#!/bin/bash
/bin/ls" >> dir/infile2' 'chmod +x dir/infile2' './dir/infile2' 'rm dir/infile2'

if [ "$MANUAL" = true ] ; then
echo
echo -e "$YELLOW---The following should be done manually...$DEFAULT"
test './minishell'
test '.env'
fi

echo -e "$YELLOW---Finished$DEFAULT"

rmdir dir