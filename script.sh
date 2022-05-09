#!/bin/bash

EXIT_CODES=true
SHOW_CMD=true
CHECK_FD=true
MANUAL=false
PROMPT="minishell$ "
ERR_ID="minishell: "

DEFAULT='\033[0m'
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
CYAN='\033[0;36m'

make | grep -v "make: Nothing"

mkdir dir
rm -rf log

test()
{
	for CMD in "$@" ; do	
		if [ "$SHOW_CMD" = true ] ; then
			echo -ne "$CYAN$CMD: $DEFAULT"
		fi
		echo $CMD >> dir/cmdlist
	done

	if [ "$EXIT_CODES" = true ] ; then
		echo 'echo exit code: $?' >> dir/cmdlist
	fi

	if [ "$CHECK_FD" = true ] ; then
		echo "lsof -a -c minishell -d 0-256 | tail -n +2 | awk '{print \$4}'" >> dir/cmdlist
	fi

	./minishell < dir/cmdlist > dir/minishell_out 2> dir/minishell_error

	sed -i '' "s/^$PROMPT//" dir/minishell_out
	sed -i '' "s/^$ERR_ID//" dir/minishell_error
	sed -i '' "s/^line [[:digit:]]://" dir/minishell_error

	sed -i '' 's/-c minishell/-p $$/' dir/cmdlist

	bash < dir/cmdlist > dir/bash_out 2> dir/bash_error

	sed -i '' "s/^bash: //" dir/bash_error
	sed -i '' "s/^line [[:digit:]]: //" dir/bash_error

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

	rm -f dir/*
}

echo -e "$YELLOW--- echo test suite ---$DEFAULT"
test 'ech'
test 'echo'
test 'echo -n'
test 'echo -1'
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
test 'echo a     b'
test 'echo "a    b"'
test 'ls | echo a b'
test 'ls | echo'
test 'ls | echo -n'
test 'ls notadir' 'echo'

echo -e "$YELLOW--- cd test suite ---$DEFAULT"
test 'c'
test 'cd /'
test 'cd $HOME' 'cd ..'
test 'cd nonexistent_dir'
test 'cd cd cd'
test 'cd src/ ..'
test 'cd pwd'
test 'ls' 'cd /' 'ls'
test 'ls' 'cd ..' 'ls'
test 'ls' 'cd notadir'
test 'ls notadir' 'cd .'

echo
echo -e "$YELLOW--- pwd test suite ---$DEFAULT"
test 'pw'
test 'pwd'
test 'unset PWD' 'pwd'
test '/pwd'
test 'pwd' 'cd ..' 'pwd'
test 'pwd' 'cd /' 'pwd'
test 'ls notadir' 'pwd'

echo
echo -e "$YELLOW--- export test suite ---$DEFAULT"
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
test 'unse PWD' 'echo $PWD'
test 'unset'
test 'echo $PWD' 'unset PWD' 'echo $PWD'
test 'pwd' 'cd ..' 'pwd' 'cd $HOME' 'pwd'
test 'mkdir test' 'cd test' 'pwd' 'rmdir ../test' 'pwd' 'cd ..' 'pwd'
test 'ls notadir' 'unset'

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
test 'exit' 'echo'

echo
echo -e "$YELLOW--- env commands test suite...$DEFAULT"
test 'en'
test 'env | grep PWD'
test 'env | grep PWD' 'unset PWD' 'env | grep PWD'

echo
echo -e "$YELLOW--- Lexer test suite ---$DEFAULT"
test ''	
test ' '	#space
test '	'	#tab
test ' 	 '	#mixed
test 'ls -a | echo -n'
test 'cat -e cat -e cat -e cat -e cat -e cat -e'
test 'cat cat cat cat cat cat cat'
test 'no_command'
test 'echo <<>><>|$|	'
test 'echo "<<">>dir/a"<">/dev/null "|$PWD|"	'
test 'export x=' 'echo -$x-'
test 'export x=_' 'echo _$x_'
test "export x='\"a   b\"'" 'echo $x'

echo
echo -e "$YELLOW--- General commands test suite ---$DEFAULT"
# commands (PATH)
test 'ls'
test 'ls -a'
test 'ls not_a_dir'
test 'cat Makefile src'
test 'not_a_command'
test 'git log -5 --pretty="format:%H"'
test 'sh -c exit'
test 'bash -c exit'
test 'export MSG="Hello "' 'bash -c "echo $MSG"'
test '/'
test 'a/'
test '/b'
test 'a/b'
test 'dir/infile'
test '/usr/bin/git status'

echo
echo -e "$YELLOW--- dollar expansion test suite ---$DEFAULT"
test 'echo ""'
test 'echo " "'
test 'echo a""'
test 'echo a""b'
test 'echo a"b"c'
test 'echo a "b" c'
test "echo '\"'\"a\""
test 'ls' 'echo $?'
test 'ls notadir' 'echo $?'
test 'echo $PWD'
test 'echo $NONEXISTING'
test "echo \"''\" \"''\" \"a\" \"$\" \"$\""
test 'echo -$PWD$?$PATH-'
test 'echo -$a$.$PW$SHLVL"$P"WD'
test 'export WORD="a   b"' 'echo $WORD'
test 'export LS="ls -a"' '$LS'
test 'export LS="s -a' 'l$LS'
test 'export PIPE="|"' 'ls $PIPE cat'
test 'echo "a$PWD-b"'

echo
echo -e "$YELLOW--- heredoc test suite ---$DEFAULT"
test '<<'
test '<< x cat' 'hey' 'not x' 'xpartway' 'x'
test '<<x' 'now' 'without' 'space' 'x'
test '<< x'
test '<<x'
test '<<x <Makefile cat' 'x'
test '<Makefile <<x cat' 'x'
test 'export x=end' 'cat << $x' 'end' 'x' '$x'
test 'export x=end' 'cat <<$x' 'end' 'x' '$x'
test '<<$'
test '<<$HOME' "$HOME" '$HOME'
test 'export END="eof"' '<<$END' 'eof' 'END' '$END'

echo
echo -e "$YELLOW--- redirect test suite ---$DEFAULT"
test 'ls > dir/outfile'
test 'ls>dir/outfile'
test '> dir/outfile'
test '< dir/outfile'
test '<'
test '>'
test '>>'
test 'touch dir/infile' '< dir/infile'
test 'echo a > dir/infile b' '< dir/infile cat'
test 'ls > dir/outfile' '> dir/outfile' 'cat dir/outfile'

echo
echo -e "$YELLOW--- pipe test suite ---$DEFAULT"
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

echo
echo -e "$YELLOW--- mixed test suite ---$DEFAULT"
test 'ls > dir/test_log | cat'
test '> log | cat'
test '< | >'
test '< Makefile cat | xargs > dir/outfile'
test 'cat<Makefile|>dir/outfile xargs'
test '<Makefile|>dir/outfile'
test '< dir/infile | > dir/outfile'
test 'cat Makefile > dir/infile' 'cat < dir/ | wc -w |  > dir/outfile'
test "head -10 <Makefile | sed -n 'g/USER/p'>dir/outfile"
test 'echo "./minishell" | ./minishell'
test 'echo "#!/bin/bash
/bin/ls" >> dir/infile' 'chmod +x dir/infile' './dir/infile' 'rm dir/infile'

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
test 'export WORD="a   b"' 'echo $WORD'
test 'cat | ls'

fi

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
test 'ls | echo -n bla'

test 'export ='
test 'export =10'
test 'export "|"=10'
test 'export ">"=10'
test 'export "$"=10'
test 'export "["=10'
test 'export "111"="222"'

echo
echo -e "$YELLOW---Finished$DEFAULT"

rm -r dir
