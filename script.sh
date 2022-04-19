#!/bin/bash

#lsof -p $$ -a -d 0-256 | tail -n +2 | awk '{print $4}'

EXIT_CODES=true
SHOW_CMD=true
#$$ needs to expands to pid
CHECK_FD=true
MANUAL=false
BASH=false

RED='\033[0;31m'
CYAN='\033[0;36m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
DEFAULT='\033[0m'

make | grep -v "make: Nothing"

rm -r dir
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

	if [ "$CHECK_FD" = true ] ; then
		echo "lsof -p \$\$ -a -d 0-256 | tail -n +2 | awk '{print \$4}'" >> dir/infile
	fi

	./minishell < dir/infile > dir/minishell_out 2> dir/minishell_error

	if grep -q "minishell" dir/minishell_error ; then
		cut -d ' ' -f 2- dir/minishell_error > dir/tmp
		cat dir/tmp > dir/minishell_error
	fi

	if grep -q "line " dir/minishell_error ; then
		cut -d ' ' -f 3- dir/minishell_error > dir/tmp
		cat dir/tmp > dir/minishell_error
	fi

	bash < dir/infile > dir/bash_out 2> dir/bash_error

	if grep -q "bash" dir/bash_error ; then
		cut -d ' ' -f 2- dir/bash_error > dir/tmp
		cat dir/tmp > dir/bash_error
	fi

	if grep -q "line " dir/bash_error ; then
		cut -d ' ' -f 3- dir/bash_error > dir/tmp
		cat dir/tmp > dir/bash_error
	fi

	if grep -q "syntax error" dir/bash_error ; then
		echo "syntax error" > dir/bash_error
	fi

	if grep -q "syntax error" dir/minishell_error ; then
		echo "syntax error" > dir/minishell_error
		echo -n > dir/minishell_out 
	fi

	diff dir/bash_out dir/minishell_out | tail -n +2 | grep -e "< " -e "> " >> dir/diff
	diff dir/bash_error dir/minishell_error | tail -n +2 | grep -e "< " -e "> " >> dir/diff


	if [ -s dir/diff ] ; then
		echo $1 >> log
		cat dir/diff >> log
		echo -e $RED[KO] $DEFAULT
		cat < dir/diff
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
test 'echo -1'
test 'echo $PWD'
test 'echo $NONEXISTING'
test 'echo a b c'
test 'echo a b	c'
test 'echo "a b  c"'
test 'echo forrest'
test 'echo - a'
test 'echo a -n'
test 'echo --n a'
test 'echo n- a'
test 'echo n a'
test 'echo -n a'
test 'echo -nABC'
test 'echo -n -n'
test 'echo a     b'
test 'echo "a    b"'
#test 'echo -nn' bash is stupid
test 'ls | echo a b'
test 'ls | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | ls'
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
test 'export LS="ls -a"' '$LS'
test 'export LS="s -"' '"l"$LS"a"'
 

echo
echo -e "$YELLOW--- unset test suite ---$DEFAULT"
# Pwd tests
test 'unse PWD' 'echo $PWD'
test 'unset'
test 'echo $PWD' 'unset PWD' 'echo $PWD'
test 'pwd' 'cd ..' 'pwd' 'cd $HOME' 'pwd'
test 'mkdir test' 'cd test' 'pwd' 'rmdir ../test' 'pwd' 'cd ..' 'pwd'

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
test 'exit 3 a'
test 'exit -3 a'

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
test 'echo "<<">>dir/a"<">/dev/null"|$PWD|"	'
test 'export x=' 'echo -$x-' 'export x=_' 'echo _$x_'

echo
echo -e "$YELLOW--- General commands test suite ---$DEFAULT"
# commands (PATH)
test 'ls'
test 'ls -a'
test 'ls not_a_dir'
test 'cat Makefile minishell'
test 'not_a_command'
test 'git log --pretty="format:%H"'
test 'sh -c exit'
test 'bash -c exit'
test 'export MSG="Hello "' 'bash -c "echo $MSG"'
test '/'
test 'a/'
test '/b'
test 'a/b'
test '/dir/infile'
test '/usr/bin/git status'
test 'cat | ls'

#redirects
test 'ls > dir/outfile'
test 'ls>dir/outfile'
test '> dir/outfile'
test '< dir/outfile'

# pipes
test '|'
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
test ''

# pipes combined with redirects
test '< Makefile cat | xargs > dir/outfile'
test 'cat<Makefile|>dir/outfile xargs'
test '<Makefile|>dir/outfile'

#test 'sleep 1 | ls test'	subject requires most _recent_ exit code

test "head -10 <Makefile | sed -n '///'>dir/outfile"
test 'echo "./minishell" | ./minishell'
test 'echo "#!/bin/bash
/bin/ls" >> dir/infile2' 'chmod +x dir/infile2' './dir/infile2' 'rm dir/infile2'

echo
echo -e "$YELLOW--- heredoc test suite ---$DEFAULT"
test '<< x cat' 'hey' 'not x' 'xpartway' 'x'
test '<<x' 'now' 'without' 'space' 'x'
test '<<'
test '<< x'
test '<<x'
test '<<x <Makefile cat' 'x'
test '<Makefile <<x cat' 'x'
test 'export x=end' 'cat << $x' 'end' 'x' '$x'
test 'export x=end' 'cat <<$x' 'end' 'x' '$x'

if [ "$MANUAL" = true ] ; then

echo
echo -e "$YELLOW---The following should be done manually...$DEFAULT"
#bash adds to env
test 'env'
#bash tries to complete pipe
test 'ls|'
test 'ls |'
#infile gets taken over
test 'bash'
test './minishell'
test 'zsh'

fi

test 'export bla="s -a"\nl$bla'
test 'export bla="s -a"\nl"$bla"'

# Generic tests
test ''
test '/bin/ls'

# Echo tests
test 'echo'
test 'echo ""'
test 'echo < |'
test 'echo > |'
test 'echo << |'
test 'echo >> |'
test 'echo -nABC'
test 'echo $BLA$BLA=10$BLA'
test 'echo a"bc"d'
test 'echo a"bcd"e'
test "echo 'hoi'"'"bla"'
test 'echo -n'
test 'echo bla -n'
test 'echo -n -n -n'
test 'echo -n -n -n bla'
test 'ls | echo -n bla'

test 'export ='
test 'export =10'
test 'export "|"=10'
test 'export ">"=10'
test 'export "$"=10'
test 'export "["=10'
test 'export "111"="222"'

if [ "$BASH" = true ] ; then

echo
echo -e "$YELLOW---The following should fail...$DEFAULT"
test '.'
test 'test sleep 1 | ls test'
test 'echo hey | kill -QUIT $$'
test 'kill -QUIT $$'
test 'kill -INT $$'
test 'echo -nn'
#test 'lsof | echo a'

fi

echo
echo -e "$YELLOW---Finished$DEFAULT"

rm -r dir