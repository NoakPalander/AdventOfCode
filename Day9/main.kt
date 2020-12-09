import java.io.File

fun Read(filename: String): List<Long> = File(filename).readLines().map { it.toLong() }

fun Part1(filename: String, preamble: Int): Long {
    fun FindPairs(data: List<Long>, target: Long): Boolean {
        return data.mapNotNull { first ->
            data.find { second ->
                first + second == target && first != second
            }
        }.isNotEmpty()
    }

    val data = Read(filename)
    for (index in preamble until data.size) {
        if (!FindPairs(data.subList(index - preamble, index), data[index]))
            return data[index]
    }

    throw RuntimeException("Unable to parse result!")
}

fun Part2(filename: String, preamble: Int): Long {
    val data = Read(filename)
    val target = Part1(filename, preamble)

    for (index in data.indices) {
        for (reversed in data.size - 1 downTo index + 1) {
            val sublist = data.subList(index, reversed + 1).toSortedSet()
            if (sublist.sum() == target)
                return sublist.first() + sublist.last()
        }
    }

    throw RuntimeException("Unable to parse result!")
}

fun main(args: Array<String>) {
    println("Part 1: ${Part1("input.txt", 25)}")
    println("Part 2: ${Part2("input.txt", 25)}")
}