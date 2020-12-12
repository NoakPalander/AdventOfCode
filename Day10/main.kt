import java.io.File

fun read(filename: String) = File(filename).readLines()
        .map { it.toInt() }
        .sorted()
        .toMutableList()
        .apply {
            add(0, 0)
            add(last() + 3)
        }

fun part1(filename: String): Int {
    val diffs = hashMapOf<Int, Int>()
    read(filename).zipWithNext { a, b ->
        diffs[b - a] = diffs[b - a]?.plus(1) ?: 1
    }

    return diffs[1]!! * diffs[3]!!
}

fun part2(filename: String): Long {
    return arrayListOf(arrayListOf<Int>()).apply {
        read(filename).zipWithNext { i, j -> j - i }.zipWithNext { current, next ->
            if (current == 1)
                last().add(current)

            if (next != 1)
                add(arrayListOf())
        }
    }.mapNotNull {
            when (it.sum()) {
                2 -> 2L
                3 -> 4L
                4 -> 7L
                else -> null
            }
    }.reduce(Long::times)
}

fun main() {
    println("Part 1: ${part1("input.txt")}")
    println("Part 2: ${part2("input.txt")}")
}