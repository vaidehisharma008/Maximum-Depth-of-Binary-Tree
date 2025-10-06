import java.util.*;

class WordLadder {
    public int ladderLength(String beginWord, String endWord, List<String> wordList) {
        // Convert wordList to a Set for O(1) average time lookups.
        Set<String> wordSet = new HashSet<>(wordList);
        
        // Edge Case: If endWord is not in the dictionary, a path is impossible.
        if (!wordSet.contains(endWord)) return 0;
        
        Queue<String> queue = new LinkedList<>();
        queue.offer(beginWord);
        
        if (wordSet.contains(beginWord)) wordSet.remove(beginWord);

        int length = 1;

        // BFS Traversal
        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            length++;
            
            for (int i = 0; i < levelSize; i++) {
                String currentWord = queue.poll();
                char[] charArray = currentWord.toCharArray();
                for (int j = 0; j < charArray.length; j++) {
                    char originalChar = charArray[j];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == originalChar) continue;
                        charArray[j] = c;
                        String transformedWord = new String(charArray);
                        if (transformedWord.equals(endWord)) return length;
                        if (wordSet.contains(transformedWord)) {
                            queue.offer(transformedWord);
                            wordSet.remove(transformedWord);
                        }
                    }
                    // Backtrack to the original character for the next iteration
                    charArray[j] = originalChar; 
                }
            }
        }
        // No Path: If the queue is empty and endWord was not reached.
        return 0;
    }
}

// Example Usage (for testing locally):

public class Main {
    public static void main(String[] args) {
        WordLadder solver = new WordLadder();
        String beginWord = "hit";
        String endWord = "cog";
        // Sample test cases
        // List<String> wordList = Arrays.asList("hot", "dot", "dog", "lot", "log", "cog"); // Output: 5
        List<String> wordList = Arrays.asList("hot", "dot", "dog", "lot", "log"); // Output: 0
        int result = solver.ladderLength(beginWord, endWord, wordList);
        System.out.println("The length of the shortest transformation sequence is: " + result); 
    }
}