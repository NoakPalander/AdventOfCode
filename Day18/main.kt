import java.io.File

fun solve(equation: Iterator<Char>): Long {
    val numbers = mutableListOf<Long>()
    var op = '+'
    while (equation.hasNext()) {
        when (val next = equation.next()) {
            '(' -> numbers += solve(equation)
            ')' -> break
            in "+*" -> op = next
            else -> numbers += next.toString().toLong()
        }

        if (numbers.size == 2) {
            val a = numbers.removeLast()
            val b = numbers.removeLast()
            numbers += if (op == '+') a + b else a * b
        }
    }
    return numbers.first()
}

fun part1(input: String): Number = File(input).readLines().map { it.replace(" ", "") }.sumOf {
    solve(it.iterator())
}


fun main() {
    println("Part 1: ${part1("input.txt")}")
}