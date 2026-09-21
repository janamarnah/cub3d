#!/bin/bash
BIN=./cub3D
PASS=0
FAIL=0
TMP=.cub3d_test_output

echo "=== BUILD ==="
make re || exit 1

echo
echo "=== INVALID MAPS: every one must print Error and exit non-zero ==="
for f in maps/tests/invalid/*; do
	$BIN "$f" >"$TMP" 2>&1
	code=$?
	if [ $code -ne 0 ] && grep -a -q "^Error" "$TMP"; then
		printf "[PASS] %s\n" "$f"
		PASS=$((PASS + 1))
	else
		printf "[FAIL] %s (exit=%d)\n" "$f" "$code"
		cat "$TMP"
		FAIL=$((FAIL + 1))
	fi
done

echo
echo "=== ARGUMENT TESTS ==="
test_arg()
{
	"$@" >"$TMP" 2>&1
	code=$?
	if [ $code -ne 0 ] && grep -a -q "^Error" "$TMP"; then
		printf "[PASS] %s\n" "$*"
		PASS=$((PASS + 1))
	else
		printf "[FAIL] %s\n" "$*"
		cat "$TMP"
		FAIL=$((FAIL + 1))
	fi
}
test_arg "$BIN"
test_arg "$BIN" maps/valid.cub extra
test_arg "$BIN" maps/tests/invalid/27_wrong_extension.txt
rm -f "$TMP"

echo
echo "PASS=$PASS FAIL=$FAIL"
echo "Valid maps are interactive and must be launched manually:"
for f in maps/tests/valid/*.cub; do
	echo "  $BIN $f"
done
