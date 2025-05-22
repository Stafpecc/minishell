#!/bin/sh

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
TOTAL=0
SUCCESS=0
MINISHELL=./exec/minishell
TMP_DIR=$(mktemp -d)
BASH_OUT="$TMP_DIR/bash_out"
MINI_OUT="$TMP_DIR/mini_out"

run_test() {
    CMD="$1"
    printf "%s\n" "$CMD" | bash 2>&1 >"$BASH_OUT"
    printf "%s\n" "$CMD" | $MINISHELL 2>&1 >"$MINI_OUT"
    EXPECTED=$(cat "$BASH_OUT")
    ACTUAL=$(cat "$MINI_OUT")
    TOTAL=$((TOTAL + 1))

    if [ "$EXPECTED" = "$ACTUAL" ]; then
        SUCCESS=$((SUCCESS + 1))
        printf "${GREEN}[OK]${NC} %s\n" "$CMD"
    else
        printf "${RED}[KO]${NC} %s\n" "$CMD"
        printf "${RED}--- Expected ---${NC}\n%s\n" "$EXPECTED"
        printf "${RED}--- Actual -----${NC}\n%s\n" "$ACTUAL"
    fi
}

# builtin
run_test "echo hello"
run_test "echo hello world"
run_test "pwd"
run_test "ls"
run_test "ls -l"
run_test "cd /tmp && pwd"
run_test "export VAR=42 && echo \$VAR"
run_test "unset VAR && echo \$VAR"
run_test "env"
run_test "whoami"
run_test "echo ok ; echo yes"
run_test "echo no && echo yes"
run_test "false && echo willnotprint"
run_test "true || echo willnotprint"
run_test "echo A || echo B"
run_test "echo A && echo B"
run_test "echo one > $TMP_DIR/f1 && cat $TMP_DIR/f1"
run_test "echo two >> $TMP_DIR/f1 && cat $TMP_DIR/f1"
run_test "cat < $TMP_DIR/f1"
run_test "cat nofile 2>&1"
run_test "echo start | cat | grep s"
run_test "echo line1\nline2 | wc -l"
run_test "cd /doesnotexist 2>&1"
run_test "ls | grep minishell"
run_test "export A=hello B=world && echo \$A \$B"
run_test "echo \$HOME"
run_test "echo \$UNSET_VAR"
run_test "echo \"quoted word\""
run_test "echo 'single quoted'"
run_test "echo \"mix \$HOME and text\""
run_test "echo \"\$((2 + 2))\""
run_test "exit"

# other_test
run_test "echo hello && false || echo fallback"
run_test "true && false || true && echo final"
run_test "mkdir -p $TMP_DIR/testdir && cd $TMP_DIR/testdir && pwd"
run_test "echo \$? after command"
run_test "cd /tmp && echo \$PWD"
run_test "touch $TMP_DIR/file && [ -f $TMP_DIR/file ] && echo exists"
run_test "[ 1 -eq 1 ] && echo equal"

# pipe_test
run_test "echo 'one two three' | wc -w"
run_test "ls -l | grep '^d'"
run_test "cat /etc/passwd | grep root | wc -l"
run_test "echo test | tee $TMP_DIR/outfile | cat"
run_test "seq 1 5 | paste -sd+ | bc"
run_test "echo -e 'a\nb\nc' | sort | head -n 1"

# redirect_test
run_test "echo redirected > $TMP_DIR/testfile && cat $TMP_DIR/testfile"
run_test "echo append >> $TMP_DIR/testfile && cat $TMP_DIR/testfile"
run_test "cat < $TMP_DIR/testfile"
run_test "cat < $TMP_DIR/doesnotexist 2>&1"
run_test "echo error > /dev/stderr"
run_test "echo output 1> $TMP_DIR/stdout && cat $TMP_DIR/stdout"
run_test "echo error 2> $TMP_DIR/stderr && cat $TMP_DIR/stderr"

printf "\nTotal: %d | Passed: ${GREEN}%d${NC} | Failed: ${RED}%d${NC}\n" "$TOTAL" "$SUCCESS" "$((TOTAL - SUCCESS))"
rm -rf "$TMP_DIR"
