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
	x=$?
	#Bash gives line number with certain errors: we cut those
	if grep -q "line " dir/tmp
	then
		cut -d ' ' -f 4- dir/tmp > dir/bash_error
	else
		cut -d ' ' -f 2- dir/tmp > dir/bash_error
	fi
	echo "exit code: $x" >> dir/bash_out

	rm -f dir/tmp

	echo $1 | ./minishell > dir/minishell_out 2> dir/tmp2
	x=$?
	cut -d ' ' -f 2- dir/tmp2 > dir/minishell_error
	echo "exit code: $x" >> dir/minishell_out

	rm -f dir/tmp
	diff dir/bash_out dir/minishell_out | tail -n +2 | grep -e "< " -e "> " >> dir/tmp
	diff dir/bash_error dir/minishell_error | tail -n +2 | grep -e "< " -e "> " >> dir/tmp

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

# basic tests
test ''	
test ' '	#space
test '	'	#tab
test ' 	 '	#mixed

# commands (PATH)
test 'ls'
test 'ls -a'
test 'ls not_a_dir'
test 'cat Makefile minishell'
test 'not_a_command'
test 'git log --pretty="format:%H"'
test 'bash'
test 'sh'

: << FAIL

# commands (relative path)
test '.'
test './'
test './minishell'
test 'kill'

FAIL

# commands (absolute path)\
test '/bin/bash'
test '/usr/bin/git status'

# custom binary
test './file' "# Doesn't exist"
echo '#!/bin/bash
ls' > file
test './file' "# No exec permission"
chmod a+x file
test './file' "# ls"
rm file

# pipes
test '|'
test 'ls |'
test '| ls'
echo -e "$CYAN---Finished$DEFAULT"

rmdir dir