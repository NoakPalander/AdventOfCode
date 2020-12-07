import java.io.File

fun Part1(data: List<String>): Int = with(data.map { it.toInt() }) {
    filter { contains(2020 - it) }.reduce { acc, elem ->  acc * elem }
}

fun Part2(data: List<String>): Int = with(data.map { it.toInt() }) {
    filter { first -> any { contains(2020 - first - it) } }.reduce{ acc, elem -> acc * elem}
}

fun main(args: Array<String>) {
    val input = File("input.txt").readLines()
    println("Part 1: ${Part1(input)}")
    println("Part 2: ${Part2(input)}")
}