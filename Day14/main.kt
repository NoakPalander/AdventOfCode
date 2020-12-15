import java.io.File
import kotlin.math.pow

data class Program(var mask: String = "", var instr: MutableList<Pair<Int, Int>> = mutableListOf())

fun readToProgram(filename: String): List<Program> {
    val programs = mutableListOf<Program>()
    File(filename).readLines().forEach { line ->
        if (line.startsWith("mask"))
            programs.add(Program(mask = line.substring(line.indexOf('=') + 2)))
        else
            programs.last().instr.add(Pair(line.substring(line.indexOf('[') + 1, line.indexOf(']')).toInt(),
                    line.substring(line.indexOf('=') + 2).toInt()))
    }
    
    return programs
}

fun part1(filename: String): Long {
    val data: List<Program> = readToProgram(filename)
    val memory = hashMapOf<Int, Long>()

    data.forEach { program ->
        program.instr.forEach { (pos, value) ->
            val binaryStr = Integer.toBinaryString(value).padStart(program.mask.length, '0')
            var computed = ""
            program.mask.forEachIndexed { idx, key ->
                if (key == 'X')
                    computed += binaryStr[idx]
                else
                    computed += Character.getNumericValue(key)
            }

            memory[pos] = computed.toLong(2)
        }
    }

    return memory.values.sum()
}

fun part2(filename: String): Long {
    val data: List<Program> = readToProgram(filename)
    val memory = hashMapOf<Long, Long>()

    data.forEach { program ->
        program.instr.forEach { (pos, value) ->
            val binaryStr = Integer.toBinaryString(pos).padStart(program.mask.length, '0')
            var computed = ""
            program.mask.forEachIndexed { idx, key ->
                computed += if(key == '0') binaryStr[idx] else key
            }


            val floating = computed.mapIndexedNotNull { index, key -> if (key == 'X') index else null }
            for (i in 0 until 2F.pow(floating.size).toInt()) {
                val curr = computed.split("").filterNot{ it == " " || it.isEmpty() }.map { it[0] }.toMutableList()
                var binary = ""
                for (a in 0 until (floating.size - Integer.toBinaryString(i).length))
                    binary += "0"

                binary += Integer.toBinaryString(i)
                floating.zip(binary.toList()).forEach { curr[it.first] = it.second }
                memory[curr.joinToString("").toLong(2)] = value.toLong()
            }
        }
    }

    return memory.values.sum()
}

fun main() {
    println("Part 1: ${part1("input.txt")}")
    println("Part 2: ${part2("input.txt")}")
}