#!/bin/bash
: ' Author: Ruben Nijhuis (rnijhuis), Maarten Joosten (mjoosten)
    General purpose tester for Mini Shell
    Compares the output of bash to Mini Shell; everything from exit codes to prompt output
'
SHLLEVEL=$S
TEST_OUTPUT_FILE=testoutput.txt


printf "\n"
# Recreate file if not empty
if [ -s $TEST_OUTPUT_FILE ]; then
    rm -f $TEST_OUTPUT_FILE
    touch $TEST_OUTPUT_FILE
fi

# EXPORT TEST
# Succesfully export a var
echo "First test should return a lyric from Smooth criminal" >> $TEST_OUTPUT_FILE
export TESTVAR="You've been hit by- You've been hit by- A smooth criminal"
echo $TESTVAR >> $TEST_OUTPUT_FILE | cat $TEST_OUTPUT_FILE

printf "\n" >> $TEST_OUTPUT_FILE

# EXPORT TEST
# unsuccesfully export a var
echo "This test exports an incorrectly formatted variable" >> $TEST_OUTPUT_FILE
export 9="Annie, are you okay?"
echo $? >> $TEST_OUTPUT_FILE

printf "\n"