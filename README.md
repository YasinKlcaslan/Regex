Regex Parser

Entrance
Regex Parser is a Python script that takes a regex pattern and a text input from the user, processing specific metacharacters within the regex pattern. This script includes ?, |, *, +, {}, [], (), ^, $, . Recognizes and processes common regex metacharacters such as .

How to use?
Send the pattern and text as parameters using the parser(pattern, text) function.
Appropriate functions will be called automatically based on the metacharacters within the pattern.
Matches will be printed to the console.

Example:

pattern = "a?b"
text = "ab abb aabb aaabb"
parser(pattern, text)

In this example, ? We check whether the character "a" marked with the metacharacter exists.

Supported Metacharacters
?: The query sign indicates that the previous character is optional.
|: Vertical bar combines two alternative patterns.
*: An asterisk indicates zero or more occurrences of the previous character.
+: The plus sign indicates one or more occurrences of the previous character.
{}: Curly brackets indicate repetitions within a certain range.
[]: Square brackets indicate a specific set of characters.
(): Round brackets indicate grouping and subexpressions.
^: The caret makes a pattern match the beginning of the text.
$: The dollar sign makes a pattern match the end of text.
.: The dot symbol represents any single character.
