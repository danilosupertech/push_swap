#!/usr/bin/env bash
set -u

# Executor de testes de performance do push_swap (avaliação 42).
# - Compila o projeto
# - Gera entradas aleatórias ÚNICAS
# - Conta operações (linhas de output)
# - Opcionalmente valida correção se um checker estiver disponível
#
# Usage:
#   ./test_performance.sh
#   TRIALS_100=50 TRIALS_500=20 ./test_performance.sh
#
# Notas:
# - Os limites abaixo seguem o padrão mais comum do subject.
#   Se o teu enunciado for diferente, sobrepõe com variáveis de ambiente (LIMIT_*).

PROJECT_BIN=${PROJECT_BIN:-./push_swap}

NO_COLOR=${NO_COLOR:-0}

# Output por caso (arrays + PASSOU/FALHOU). Use 0 para imprimir só resumos.
SHOW_CASES=${SHOW_CASES:-1}

# Quantos números imprimir por linha ao mostrar arrays
WORDS_PER_LINE=${WORDS_PER_LINE:-20}

TRIALS_3=${TRIALS_3:-50}
TRIALS_5=${TRIALS_5:-50}
TRIALS_100=${TRIALS_100:-20}
TRIALS_500=${TRIALS_500:-10}

# Limites comuns do subject 42 (pode sobrepor se necessário)
LIMIT_100_5=${LIMIT_100_5:-700}
LIMIT_100_4=${LIMIT_100_4:-900}
LIMIT_100_3=${LIMIT_100_3:-1100}
LIMIT_100_2=${LIMIT_100_2:-1300}
LIMIT_100_1=${LIMIT_100_1:-1500}

LIMIT_500_5=${LIMIT_500_5:-5500}
LIMIT_500_4=${LIMIT_500_4:-7000}
LIMIT_500_3=${LIMIT_500_3:-8500}
LIMIT_500_2=${LIMIT_500_2:-10000}
LIMIT_500_1=${LIMIT_500_1:-11500}

# Limites esperados usados para PASSOU/FALHOU no output por caso.
# Podes sobrepor estes valores.
EXPECT_3=${EXPECT_3:-2}
EXPECT_5=${EXPECT_5:-12}

# Para N=100/500, o "esperado" é interpretado como um alvo de tier.
# - bonus: 100<=700 e 500<=5500
# - min80: passa se as médias batem uma das combinações do subject
# Podes sobrepor TIER para forçar a etiqueta de PASSOU/FALHOU.
TIER=${TIER:-bonus}

fail() {
	printf "%s\n" "$*" 1>&2
	exit 1
}

use_color() {
	[ "$NO_COLOR" -eq 0 ] && [ -t 1 ]
}

style_init() {
	if use_color; then
		C_RESET=$'\033[0m'
		C_DIM=$'\033[2m'
		C_GREEN=$'\033[32m'
		C_RED=$'\033[31m'
		C_YELLOW=$'\033[33m'
		C_BLUE=$'\033[34m'
	else
		C_RESET=""
		C_DIM=""
		C_GREEN=""
		C_RED=""
		C_YELLOW=""
		C_BLUE=""
	fi
}

banner() {
	printf "%s%s%s\n" "$C_BLUE" "$1" "$C_RESET"
}

info() {
	printf "%s%s%s\n" "$C_DIM" "$1" "$C_RESET"
}

have() {
	command -v "$1" >/dev/null 2>&1
}

find_checker() {
	# Procura nomes/localizações comuns de checker.
	if [ -x ./checker ]; then
		printf "%s" "./checker"
		return 0
	fi
	if [ -x ./checker_linux ]; then
		printf "%s" "./checker_linux"
		return 0
	fi
	if [ -x ./checker_Mac ]; then
		printf "%s" "./checker_Mac"
		return 0
	fi
	if [ -x ./checker_py.py ]; then
		printf "%s" "./checker_py.py"
		return 0
	fi
	if have checker_linux; then
		command -v checker_linux
		return 0
	fi
	if have checker; then
		command -v checker
		return 0
	fi
	return 1
}

CHECKER=""
HAVE_CHECKER=0
MANDATORY_OK=1

# Totais globais de validação via checker (provar o bônus).
CHECK_TOTAL=0
CHECK_OK=0
CHECK_BAD=0

print_sep() {
	printf "%s----------------------------------------%s\n" \
		"$C_DIM" "$C_RESET" 1>&2
}

print_args_wrapped() {
	# Prints a space-separated list in multiple lines to avoid huge/merged lines.
	local args="$1"
	local wpl="$WORDS_PER_LINE"
	local i
	local line

	i=0
	line=""
	for x in $args; do
		if [ "$i" -eq 0 ]; then
			line="$x"
		else
			line="$line $x"
		fi
		i=$((i + 1))
		if [ "$i" -ge "$wpl" ]; then
			printf "%s   %s%s\n" "$C_DIM" "$line" "$C_RESET" 1>&2
			i=0
			line=""
		fi
	done
	if [ -n "$line" ]; then
		printf "%s   %s%s\n" "$C_DIM" "$line" "$C_RESET" 1>&2
	fi
}

expected_limit() {
	local n="$1"
	if [ "$n" -eq 3 ]; then
		echo "$EXPECT_3"
		return
	fi
	if [ "$n" -eq 5 ]; then
		echo "$EXPECT_5"
		return
	fi
	if [ "$n" -eq 100 ]; then
		echo "$LIMIT_100_5"
		return
	fi
	if [ "$n" -eq 500 ]; then
		echo "$LIMIT_500_5"
		return
	fi
	echo 0
}

tier_label() {
	if [ "$TIER" = "bonus" ]; then
		echo "BONUS"
		return
	fi
	if [ "$TIER" = "min80" ]; then
		echo "80%"
		return
	fi
	echo "$TIER"
}

passes_bonus_pair() {
	local avg100="$1"
	local avg500="$2"
	[ "$avg100" -le "$LIMIT_100_5" ] && [ "$avg500" -le "$LIMIT_500_5" ]
}

passes_80_pair() {
	local avg100="$1"
	local avg500="$2"
	if [ "$avg100" -le "$LIMIT_100_3" ] && [ "$avg500" -le "$LIMIT_500_3" ]; then
		return 0
	fi
	if [ "$avg100" -le "$LIMIT_100_5" ] && [ "$avg500" -le "$LIMIT_500_1" ]; then
		return 0
	fi
	if [ "$avg100" -le "$LIMIT_100_2" ] && [ "$avg500" -le "$LIMIT_500_5" ]; then
		return 0
	fi
	return 1
}

tier_passes_pair() {
	local avg100="$1"
	local avg500="$2"
	if [ "$TIER" = "bonus" ]; then
		passes_bonus_pair "$avg100" "$avg500"
		return
	fi
	if [ "$TIER" = "min80" ]; then
		passes_80_pair "$avg100" "$avg500"
		return
	fi
	return 1
}

rand_args_py() {
	# $1 = N
	python3 - << 'PY' "$1"
import random, sys
n = int(sys.argv[1])
# Wide range to keep uniqueness easy.
vals = random.sample(range(-1000000, 1000000), n)
print(" ".join(str(x) for x in vals))
PY
}

rand_args_shuf() {
	# $1 = N
	# Fallback if python3 isn't available.
	local n="$1"
	# Ensure range is big enough.
	shuf -i -1000000:1000000 -n "$n" | tr '\n' ' '
	echo
}

rand_args() {
	local n="$1"
	if have python3; then
		rand_args_py "$n"
		return 0
	fi
	if have shuf; then
		rand_args_shuf "$n"
		return 0
	fi
	fail "Need python3 or shuf to generate random tests"
}

count_ops() {
	# Reads operations on stdin and prints the line count.
	# Works even if output is empty.
	local n
	n=$(wc -l | tr -d ' ')
	if [ -z "$n" ]; then
		n=0
	fi
	printf "%s" "$n"
}

score_100() {
	local ops="$1"
	if [ "$ops" -le "$LIMIT_100_5" ]; then echo "5"; return; fi
	if [ "$ops" -le "$LIMIT_100_4" ]; then echo "4"; return; fi
	if [ "$ops" -le "$LIMIT_100_3" ]; then echo "3"; return; fi
	if [ "$ops" -le "$LIMIT_100_2" ]; then echo "2"; return; fi
	if [ "$ops" -le "$LIMIT_100_1" ]; then echo "1"; return; fi
	echo "0"
}

score_500() {
	local ops="$1"
	if [ "$ops" -le "$LIMIT_500_5" ]; then echo "5"; return; fi
	if [ "$ops" -le "$LIMIT_500_4" ]; then echo "4"; return; fi
	if [ "$ops" -le "$LIMIT_500_3" ]; then echo "3"; return; fi
	if [ "$ops" -le "$LIMIT_500_2" ]; then echo "2"; return; fi
	if [ "$ops" -le "$LIMIT_500_1" ]; then echo "1"; return; fi
	echo "0"
}

run_one() {
	# $1 = N, $2 = CASE_INDEX, $3 = CASE_TOTAL
	# prints: "ops check"; returns 0 if ok, 1 if failed (checker KO or push_swap error)
	local n="$1"
	local case_i="${2:-0}"
	local case_total="${3:-0}"
	local args
	local ops
	local out
	local status
	local verdict
	local check

	args=$(rand_args "$n")
	out=$($PROJECT_BIN $args)
	status=$?
	if [ "$status" -ne 0 ]; then
		printf "%s\n" "push_swap retornou $status para a entrada: $args" 1>&2
		printf "%s %s" "0" "PSERR"
		return 1
	fi
	ops=$(printf "%s" "$out" | count_ops)
	check="SKIP"

	if [ "$HAVE_CHECKER" -eq 1 ]; then
		# checker reads operations from stdin
		verdict=$(printf "%s" "$out" | $CHECKER $args || true)
		check="$verdict"
	fi

	if [ "$SHOW_CASES" -eq 1 ]; then
		local exp
		local pts
		exp=$(expected_limit "$n")
		pts="-"
		if [ "$n" -eq 100 ]; then
			pts=$(score_100 "$ops")
		fi
		if [ "$n" -eq 500 ]; then
			pts=$(score_500 "$ops")
		fi
		print_sep
		if [ "$case_i" -gt 0 ] && [ "$case_total" -gt 0 ]; then
			printf "%sCaso %s/%s%s (N=%s)\n" \
				"$C_BLUE" "$case_i" "$case_total" "$C_RESET" "$n" 1>&2
		else
			printf "%sCaso%s (N=%s)\n" "$C_BLUE" "$C_RESET" "$n" 1>&2
		fi
		if [ "$check" != "SKIP" ] && [ "$check" != "OK" ]; then
			printf "%s❌ FALHOU%s check=%s ops=%s esperado<=%s pts=%s\n" \
				"$C_RED" "$C_RESET" "$check" "$ops" "$exp" "$pts" 1>&2
		elif [ "$exp" -gt 0 ] && [ "$ops" -le "$exp" ]; then
			printf "%s✅ PASSOU%s check=%s ops=%s esperado<=%s pts=%s\n" \
				"$C_GREEN" "$C_RESET" "$check" "$ops" "$exp" "$pts" 1>&2
		else
			printf "%s❌ FALHOU%s check=%s ops=%s esperado<=%s pts=%s\n" \
				"$C_RED" "$C_RESET" "$check" "$ops" "$exp" "$pts" 1>&2
		fi
		printf "%sEntrada:%s\n" "$C_DIM" "$C_RESET" 1>&2
		print_args_wrapped "$args"
	fi

	if [ "$check" != "SKIP" ] && [ "$check" != "OK" ]; then
		printf "%s\n" "KO para a entrada: $args" 1>&2
		printf "%s\n" "saída do checker: $check" 1>&2
		printf "%s %s" "$ops" "$check"
		return 1
	fi

	printf "%s %s" "$ops" "$check"
	return 0
}

stats_init() {
	# globals: SUM MIN MAX CNT FAIL
	SUM=0
	MIN=2147483647
	MAX=0
	CNT=0
	FAIL=0
}

stats_add() {
	local v="$1"
	SUM=$((SUM + v))
	if [ "$v" -lt "$MIN" ]; then MIN="$v"; fi
	if [ "$v" -gt "$MAX" ]; then MAX="$v"; fi
	CNT=$((CNT + 1))
}

stats_avg() {
	if [ "$CNT" -eq 0 ]; then
		echo 0
	else
		echo $((SUM / CNT))
	fi
}

bench() {
	# $1 = N, $2 = TESTES
	local n="$1"
	local trials="$2"
	local i
	local exp
	local pass
	local fail
	local avg
	local check_fail

	stats_init
	exp=$(expected_limit "$n")
	pass=0
	fail=0
	check_fail=0
	if [ "$SHOW_CASES" -eq 1 ]; then
		banner "N=$n (esperado <= $exp)"
	fi
	i=1
	while [ "$i" -le "$trials" ]; do
		local result
		local run_status
		local ops
		local chk
		result=$(run_one "$n" "$i" "$trials")
		run_status=$?
		ops=${result%% *}
		chk=${result#* }
		if [ "$HAVE_CHECKER" -eq 1 ]; then
			CHECK_TOTAL=$((CHECK_TOTAL + 1))
			if [ "$chk" = "OK" ]; then
				CHECK_OK=$((CHECK_OK + 1))
			else
				CHECK_BAD=$((CHECK_BAD + 1))
				check_fail=$((check_fail + 1))
				MANDATORY_OK=0
			fi
		fi
		if [ "$chk" = "" ]; then
			chk="(vazio)"
		fi
		if [ "$run_status" -ne 0 ]; then
			FAIL=$((FAIL + 1))
			fail=$((fail + 1))
			i=$((i + 1))
			continue
		fi
		stats_add "$ops"
		if [ "$exp" -gt 0 ] && [ "$ops" -le "$exp" ]; then
			pass=$((pass + 1))
		else
			fail=$((fail + 1))
		fi
		i=$((i + 1))
	done

	if [ "$fail" -eq 0 ]; then
		avg=$(stats_avg)
		printf "%s✅ PASSOU%s N=%s testes=%s media=%s min=%s max=%s (passou=%s falhou=%s)\n" \
				"$C_GREEN" "$C_RESET" "$n" "$trials" "$avg" "$MIN" "$MAX" "$pass" "$fail"
	else
			avg=$(stats_avg)
			printf "%s❌ FALHOU%s N=%s testes=%s media=%s min=%s max=%s (passou=%s falhou=%s)\n" \
				"$C_RED" "$C_RESET" "$n" "$trials" "$avg" "$MIN" "$MAX" "$pass" "$fail"
	fi

		LAST_N="$n"
		LAST_AVG="$avg"
		LAST_MIN="$MIN"
		LAST_MAX="$MAX"
		LAST_PASS="$pass"
		LAST_FAIL="$fail"
		LAST_CHECK_FAIL="$check_fail"

	if [ "$n" -eq 100 ] && [ "$CNT" -gt 0 ]; then
		printf "%s   📊 pontos100(media)=%s pontos100(max)=%s%s\n" \
			"$C_DIM" "$(score_100 "$(stats_avg)")" "$(score_100 "$MAX")" "$C_RESET"
	fi
	if [ "$n" -eq 500 ] && [ "$CNT" -gt 0 ]; then
		printf "%s   📊 pontos500(media)=%s pontos500(max)=%s%s\n" \
			"$C_DIM" "$(score_500 "$(stats_avg)")" "$(score_500 "$MAX")" "$C_RESET"
	fi
	:
}

report_print() {
	local mandatory
	local tier
	local total_tests
	local total_pass
	local total_fail
	local total_checkfail

	mandatory="N/A"
	if [ "$HAVE_CHECKER" -eq 1 ]; then
		if [ "$MANDATORY_OK" -eq 1 ]; then
			mandatory="OK"
		else
			mandatory="FAIL"
		fi
	fi

	tier="-"
	if [ "$HAVE_CHECKER" -eq 1 ] && [ "$MANDATORY_OK" -eq 1 ]; then
		if passes_bonus_pair "$AVG_100" "$AVG_500"; then
			tier="BONUS"
		elif passes_80_pair "$AVG_100" "$AVG_500"; then
			tier="80%"
		else
			tier="FAIL"
		fi
	fi

	printf "\n"
	banner "--- Relatorio ---"
	printf "%-5s %-6s %-6s %-6s %-6s %-10s %-8s %-8s\n" \
		"N" "testes" "passou" "falhou" "máx" "esperado" "checker" "total"
	printf "%-5s %-6s %-6s %-6s %-6s %-10s %-8s %-8s\n" \
		"---" "------" "------" "------" "------" "----------" "--------" "--------"

	report_row() {
		local n="$1" trials="$2" pass="$3" fail="$4" max="$5" exp="$6" cfail="$7"
		local checker total
		checker="N/A"
		if [ "$HAVE_CHECKER" -eq 1 ]; then
			if [ "$cfail" -eq 0 ]; then
				checker="OK"
			else
				checker="FAIL"
			fi
		fi
		total="FAIL"
		if [ "$checker" != "FAIL" ] && [ "$fail" -eq 0 ]; then
			total="OK"
		fi
		printf "%-5s %-6s %-6s %-6s %-6s %-10s %-8s %-8s\n" \
			"$n" "$trials" "$pass" "$fail" "$max" "<=$exp" "$checker" "$total"
	}

	report_row 3 "$TRIALS_3" "$PASS_3" "$FAIL_3" "$MAX_3" "$(expected_limit 3)" "$CHECKFAIL_3"
	report_row 5 "$TRIALS_5" "$PASS_5" "$FAIL_5" "$MAX_5" "$(expected_limit 5)" "$CHECKFAIL_5"
	report_row 100 "$TRIALS_100" "$PASS_100" "$FAIL_100" "$MAX_100" "$(expected_limit 100)" "$CHECKFAIL_100"
	report_row 500 "$TRIALS_500" "$PASS_500" "$FAIL_500" "$MAX_500" "$(expected_limit 500)" "$CHECKFAIL_500"

	printf "\n"
	printf "OBRIGATÓRIO: %s\n" "$mandatory"
	printf "PERFORMANCE(TIER=%s): %s\n" "$(tier_label)" "$tier"

	total_tests=$((TRIALS_3 + TRIALS_5 + TRIALS_100 + TRIALS_500))
	total_pass=$((PASS_3 + PASS_5 + PASS_100 + PASS_500))
	total_fail=$((FAIL_3 + FAIL_5 + FAIL_100 + FAIL_500))
	total_checkfail=$((CHECKFAIL_3 + CHECKFAIL_5 + CHECKFAIL_100 + CHECKFAIL_500))
	printf "TOTAL: testes=%s passou=%s falhou=%s" "$total_tests" "$total_pass" "$total_fail"
	if [ "$HAVE_CHECKER" -eq 1 ]; then
		printf " (checker_falhas=%s)" "$total_checkfail"
	fi
	printf "\n"
	if [ "$HAVE_CHECKER" -eq 1 ]; then
		printf "CHECKER(bonus): usado=%s execucoes=%s OK=%s falhas=%s\n" \
			"$CHECKER" "$CHECK_TOTAL" "$CHECK_OK" "$CHECK_BAD"
	fi
}

main() {
	style_init
	banner "🧪 push_swap - performance test"
	printf "Compilando...\n"
	make -s || fail "falha no make"
	make -s bonus >/dev/null 2>&1 || true
	[ -x "$PROJECT_BIN" ] || fail "Binário não encontrado/executável: $PROJECT_BIN"

	if find_checker >/dev/null 2>&1; then
		CHECKER="$(find_checker)"
		HAVE_CHECKER=1
		printf "Checker: %s✅%s %s\n" "$C_GREEN" "$C_RESET" "$CHECKER"
	else
		HAVE_CHECKER=0
		MANDATORY_OK=0
		info "Checker: (não encontrado) -> sem validação obrigatória (bónus não será avaliado)"
	fi

	printf "\n"
	banner "--- Testes ---"
	bench 3 "$TRIALS_3"
	AVG_3="$LAST_AVG"; MIN_3="$LAST_MIN"; MAX_3="$LAST_MAX"; FAIL_3="$LAST_FAIL"; CHECKFAIL_3="$LAST_CHECK_FAIL"
	PASS_3="$LAST_PASS"
	bench 5 "$TRIALS_5"
	AVG_5="$LAST_AVG"; MIN_5="$LAST_MIN"; MAX_5="$LAST_MAX"; FAIL_5="$LAST_FAIL"; CHECKFAIL_5="$LAST_CHECK_FAIL"
	PASS_5="$LAST_PASS"

	bench 100 "$TRIALS_100"
	AVG_100="$LAST_AVG"; MIN_100="$LAST_MIN"; MAX_100="$LAST_MAX"; FAIL_100="$LAST_FAIL"; CHECKFAIL_100="$LAST_CHECK_FAIL"
	PASS_100="$LAST_PASS"

	bench 500 "$TRIALS_500"
	AVG_500="$LAST_AVG"; MIN_500="$LAST_MIN"; MAX_500="$LAST_MAX"; FAIL_500="$LAST_FAIL"; CHECKFAIL_500="$LAST_CHECK_FAIL"
	PASS_500="$LAST_PASS"

	printf "\n"
	banner "--- Resultado (médias 100/500) ---"
	info "Regras: BONUS => 100<=${LIMIT_100_5} e 500<=${LIMIT_500_5}"
	info "Regras: 80% => (100<=${LIMIT_100_3} e 500<=${LIMIT_500_3}) OR (100<=${LIMIT_100_5} e 500<=${LIMIT_500_1}) OR (100<=${LIMIT_100_2} e 500<=${LIMIT_500_5})"
	if [ "$HAVE_CHECKER" -ne 1 ]; then
		printf "%s⚠️ CORREÇÃO NÃO VERIFICADA%s (checker ausente)\n" \
			"$C_YELLOW" "$C_RESET"
		printf "%s⚠️ Resultado de performance apenas%s avg100=%s avg500=%s\n" \
			"$C_YELLOW" "$C_RESET" "$AVG_100" "$AVG_500"
	elif [ "$MANDATORY_OK" -ne 1 ]; then
		printf "%s❌ FALHOU OBRIGATÓRIO%s (checker KO/erro detectado)\n" \
			"$C_RED" "$C_RESET"
		printf "%s⚠️ Bonus não será avaliado%s\n" \
			"$C_YELLOW" "$C_RESET"
	elif passes_bonus_pair "$AVG_100" "$AVG_500"; then
		printf "%s✅ BONUS%s avg100=%s avg500=%s\n" "$C_GREEN" "$C_RESET" "$AVG_100" "$AVG_500"
	elif passes_80_pair "$AVG_100" "$AVG_500"; then
		printf "%s✅ 80%%%s avg100=%s avg500=%s\n" "$C_GREEN" "$C_RESET" "$AVG_100" "$AVG_500"
	else
		printf "%s❌ FALHOU%s avg100=%s avg500=%s\n" "$C_RED" "$C_RESET" "$AVG_100" "$AVG_500"
	fi

	printf "\nLimites (pode sobrepor via env):\n"
	printf "100: %s/%s/%s/%s/%s (níveis 5..1)\n" \
		"$LIMIT_100_5" "$LIMIT_100_4" "$LIMIT_100_3" "$LIMIT_100_2" "$LIMIT_100_1"
	printf "500: %s/%s/%s/%s/%s (níveis 5..1)\n" \
		"$LIMIT_500_5" "$LIMIT_500_4" "$LIMIT_500_3" "$LIMIT_500_2" "$LIMIT_500_1"

	report_print
}

main "$@"
