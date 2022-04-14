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

	#Bash gives line number with certain errors: we cut those
	if grep -q "line " dir/tmp
	then
		cut -d ' ' -f 4- dir/tmp > dir/bash_error
	else
		cut -d ' ' -f 2- dir/tmp > dir/bash_error
	fi
	echo $? >> dir/bash_out

	rm -f dir/tmp

	echo $1 | ./minishell > dir/minishell_out 2> dir/tmp2
	cut -d ' ' -f 2- dir/tmp2 > dir/minishell_error
	echo $? >> dir/minishell_out

	rm -f dir/tmp
	diff dir/bash_out dir/minishell_out >> dir/tmp
	diff dir/bash_error dir/minishell_error >> dir/tmp

	if [ -s dir/tmp ]
	then
		cat dir/tmp >> log
		echo -e $RED
		cat < dir/tmp
		echo -ne $DEFAULT
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

# commands
test 'ls'
test 'ls -a'
test 'ls not_a_dir'
test 'cat Makefile minishell'
test 'not_a_command'
test 'git log --pretty="format:%H"'
test './minishell'
test 'bash'
test 'sh'

# custom binary
test './file' "# Doesn't exist"
echo '#!/bin/bash
git status' > file
test './file' "# No exec permission"
chmod a+x file
test './file' "# git status"
rm file

echo -e "$CYAN---Finished$DEFAULT"

rmdir dir