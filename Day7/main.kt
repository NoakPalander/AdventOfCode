import java.io.File

fun Construct(input: List<String>): Map<String, List<Pair<Int, String>>> {
    return input.filterNot { rule ->
        // Filters out all empty bags (dead ends)
        rule.contains("no other")
    }.map { validRule ->
        // Separates the base color and the contents
        val (color, contents) = validRule.split(" bags contain ")
        color to contents.split(", ").map { children ->
            val items = children.split(" ")
            val childrenColors = items.drop(1).dropLast(1).joinToString(" ")

            // Maps the count to the child colors
            items[0].toInt() to childrenColors
        }
    }.toMap()
}

fun Part1(data: List<String>): Int {
    val bags = Construct(data)

    fun parse(bag: String): List<String> {
        val found = bags.filter { parent ->
            // Filters out all occurrences that doesn't contain golds
            parent.value.filter { pair ->
                pair.second == bag
            }.count() > 0
        }.map { parent ->
            parse(parent.key)
        }

        // Converts the array to 1D, adds the original bag item, and filters out duplicates
        return found.flatten().plus(bag).distinct()
    }

    return parse("shiny gold").distinct().size - 1
}

fun Part2(data: List<String>): Int {
    val bags = Construct(data)

    fun parse(bagColor: String): Int {
        return 1 + (bags[bagColor]?.sumBy { parse(it.second) * it.first } ?: 0)
    }

    return parse("shiny gold") - 1
}

fun main(args: Array<String>) {
    val input = File({}::class.java.getResource("/input.txt").path).readLines()
    println("Part 1: ${Part1(input)}")
    println("Part 2: ${Part2(input)}")
}