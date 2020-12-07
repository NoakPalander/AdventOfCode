import java.io.File

fun Part1(input: List<String>): Int {
    val bags = input.filterNot { it.contains("no other") }.map {
        val (color, content) = it.split(" bags contain ")
        color to content.split(", ").map {
            val items = it.split(" ")
            items[0].toInt() to items.drop(1).dropLast(1).joinToString(" ")
        }
    }.toMap()

    fun parentBags(bag: String): List<String> {
        return bags.filter {
            it.value.filter { p ->
                p.second == bag
            }.count() > 0
        }.map {
            parentBags(it.key)
        }.flatten().plus(bag).distinct()
    }

    return parentBags("shiny gold").distinct().size - 1
}

fun Part2(input: List<String>): Int {
    val bags = input.filterNot {
        it.contains("no other")
    }.map {
        val (color, content) = it.split(" bags contain ")
        color to content.split(", ").map {
            val items = it.split(" ")
            items[0].toInt() to items.drop(1).dropLast(1).joinToString(" ")
        }
    }.toMap()

    fun nestedBags(color: String): Int {
        return 1 + (bags[color]?.sumBy { nestedBags(it.second) * it.first } ?: 0)
    }

    return nestedBags("shiny gold")  - 1
}

fun main(args: Array<String>) {
    val input = File({}::class.java.getResource("/input.txt").path).readLines()
    println("Part 1: ${Part1(input)}")
    println("Part 2: ${Part2(input)}")
}