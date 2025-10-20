import java.util.*;

class Solution {
    public int minTime(Node root, int target) {
        Map<Node, Node> parentMap = new HashMap<>();
        Node targetNode = buildParentMap(root, target, parentMap);

        return burnTree(targetNode, parentMap);
    }

    private Node buildParentMap(Node root, int target, Map<Node, Node> parentMap) {
        Queue<Node> queue = new LinkedList<>();
        queue.offer(root);
        Node targetNode = null;

        while (!queue.isEmpty()) {
            Node curr = queue.poll();
            if (curr.data == target)
                targetNode = curr;

            if (curr.left != null) {
                parentMap.put(curr.left, curr);
                queue.offer(curr.left);
            }

            if (curr.right != null) {
                parentMap.put(curr.right, curr);
                queue.offer(curr.right);
            }
        }
        return targetNode;
    }

    private int burnTree(Node targetNode, Map<Node, Node> parentMap) {
        Map<Node, Boolean> visited = new HashMap<>();
        Queue<Node> queue = new LinkedList<>();
        queue.offer(targetNode);
        visited.put(targetNode, true);
        int time = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();
            boolean burnedNewNode = false;

            for (int i = 0; i < size; i++) {
                Node curr = queue.poll();

                if (curr.left != null && !visited.containsKey(curr.left)) {
                    burnedNewNode = true;
                    queue.offer(curr.left);
                    visited.put(curr.left, true);
                }

                if (curr.right != null && !visited.containsKey(curr.right)) {
                    burnedNewNode = true;
                    queue.offer(curr.right);
                    visited.put(curr.right, true);
                }

                Node parent = parentMap.get(curr);
                if (parent != null && !visited.containsKey(parent)) {
                    burnedNewNode = true;
                    queue.offer(parent);
                    visited.put(parent, true);
                }
            }

            if (burnedNewNode)
                time++;
        }
        return time;
    }
}
