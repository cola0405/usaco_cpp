import java.io.*; // 导入Java输入输出包
import java.util.*; // 导入Java实用工具包

public class TargetPractice {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in); // 创建Scanner对象读取输入
        int nloc = sc.nextInt(); // 读取靶子上标记的位置数
        int ncommands = sc.nextInt(); // 读取指令的数量
        boolean[] locations = new boolean[2 * ncommands + 5]; // 创建一个布尔数组，表示靶子上的位置是否被标记
        for (int i = 0; i < nloc; i++) {
            locations[sc.nextInt() + ncommands] = true; // 将用户输入的标记位置设置为true
        }
        String command = sc.next(); // 读取指令字符串
        HashMap<Integer, Integer> currentHit = new HashMap<>(); // 当前被击中的位置及其对应的指令索引
        HashMap<Integer, Integer> whenHit = new HashMap<>(); // 指令索引及其对应的位置
        int cur_pos = ncommands; // 当前位置初始化为靶子中心
        for (int i = 0; i < ncommands; i++) {
            if (command.charAt(i) == 'F') { // 如果指令是'F'，检查当前位置是否被标记且未被击中
                if (locations[cur_pos] && !currentHit.containsKey(cur_pos)) {
                    currentHit.put(cur_pos, i); // 记录当前位置被击中
                    whenHit.put(i, cur_pos); // 记录指令索引对应的位置
                }
            }
            cur_pos += (command.charAt(i) == 'L') ? -1 : 0; // 如果指令是'L'，向左移动
            cur_pos += (command.charAt(i) == 'R') ? 1 : 0; // 如果指令是'R'，向右移动
        }
        int max = currentHit.size(); // 初始化最大击中数为当前击中数
        HashSet[] rightSide = new HashSet[5]; // 创建5个HashSet，用于存储可能的右侧击中位置
        for (int i = 0; i < 5; i++) rightSide[i] = new HashSet<Integer>(); // 初始化这些HashSet
        HashSet[] toBeAdded = new HashSet[5]; // 创建5个HashSet，用于存储将要添加的位置
        for (int i = 0; i < 5; i++) toBeAdded[i] = new HashSet<Integer>(); // 初始化这些HashSet
        for (int i = ncommands - 1; i >= 0; i--) { // 从最后一个指令开始逆向遍历
            if (whenHit.containsKey(i)) { // 如果当前指令索引在whenHit中存在
                currentHit.remove(whenHit.get(i)); // 从currentHit中移除对应的位置
                whenHit.remove(i); // 从whenHit中移除对应的指令索引
                for (int j = 0; j < 5; j++) { // 遍历5个HashSet
                    if (toBeAdded[j].contains(cur_pos)) { // 如果toBeAdded中包含当前位置
                        rightSide[j].add(cur_pos); // 将当前位置添加到rightSide中
                        toBeAdded[j].remove(cur_pos); // 从toBeAdded中移除当前位置
                    }
                }
            }
            cur_pos += (command.charAt(i) == 'L') ? 1 : 0; // 如果指令是'L'，向右移动
            cur_pos += (command.charAt(i) == 'R') ? -1 : 0; // 如果指令是'R'，向左移动
            switch (command.charAt(i)) { // 根据当前指令进行不同的操作
                case 'L':
                    // 尝试'F'操作并添加所有位移为1的位置
                    int addL = locations[cur_pos] && !currentHit.containsKey(cur_pos) && !rightSide[3].contains(cur_pos) ? 1 : 0;
                    max = Math.max(max, whenHit.size() + addL + rightSide[3].size());
                    // 尝试改变到'R'
                    max = Math.max(max, whenHit.size() + rightSide[4].size());
                    break;
                case 'R':
                    // 尝试'F'操作并添加所有位移为1的位置
                    int addR = locations[cur_pos] && !currentHit.containsKey(cur_pos) && !rightSide[1].contains(cur_pos) ? 1 : 0;
                    max = Math.max(max, whenHit.size() + addR + rightSide[1].size());
                    // 尝试改变到'L'
                    max = Math.max(max, whenHit.size() + rightSide[0].size());
                    break;
                case 'F':
                    // 尝试改变到'L'
                    max = Math.max(max, whenHit.size() + rightSide[1].size());
                    // 尝试改变到'R'
                    max = Math.max(max, whenHit.size() + rightSide[3].size());
                    break;
            }
            if (command.charAt(i) == 'F') { // 如果指令是'F'
                for (int j = cur_pos - 2; j <= cur_pos + 2; j++) { // 遍历当前位置左右各2个位置
                    if (j < 0 || j >= locations.length) continue; // 如果位置超出数组范围，跳过
                    if (locations[j]) { // 如果该位置被标记
                        if (currentHit.containsKey(j)) { // 如果该位置已经被击中
                            toBeAdded[j - cur_pos + 2].add(j); // 将该位置添加到toBeAdded中
                        } else { // 如果该位置未被击中
                            rightSide[j - cur_pos + 2].add(j); // 将该位置添加到rightSide中
                        }
                    }
                }
            }
        }
        System.out.println(max); // 输出最大击中数
    }
}