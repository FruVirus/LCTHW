echo "Running unit tests:"

for i in tests/*_tests
do
    # '-f file': True if 'file' exists and is a regular file.
    # The 'test' command is a builtin which tests file types and compares strings. Therefore, in a Bash script, 'test' does not call the external /usr/bin/test binary.
    if test -f $i
    then
        # The '>>' operator generally enables output redirection to a file and appending to it instead of replacing it (the '>' operator replaces).
        # A number in front of any redirection operator defines the stream number to be redirected, in this case 'stderr'.
        # Thus, 'some-command 2>> file' appends the 'stderr'-outputs of 'some-command' to the file 'file'.
        if $VALGRIND ./$i 2 >> tests/tests.log
            then
                echo $i PASS
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            exit 1
        fi
    fi
done

echo ""
