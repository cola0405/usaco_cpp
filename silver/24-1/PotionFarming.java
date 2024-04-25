import java.util.*;
import java.io.*;
 
public class PotionFarming {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        int s = 0;
        int[] pots = new int[n];
        int i = 0;
        for (String potion : in.readLine().split(" ")) {
            pots[i++] = Integer.parseInt(potion)-1;
        }
        ArrayList[] graph = new ArrayList[n];
        for (i = 0; i < n; i++) {
            graph[i] = new ArrayList();
        }
        for (i = 0; i < n - 1; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(tokenizer.nextToken()) - 1;
            int b = Integer.parseInt(tokenizer.nextToken()) - 1;
            graph[a].add(b);
            graph[b].add(a);
        }
        numleaves = new int[n];
        int leaves = countleaves(s, -1, graph);
        int[] modpots = new int[n];
        for (i = 0; i < leaves; i++) {
            modpots[pots[i]]++;
        }
        System.out.println(countPotions(s, -1, graph, modpots));
    }
    public static int countPotions(int cur, int par, ArrayList[] graph, int[] modpots){
        int sum = 0;
        for (Object a : graph[cur]){
            if ((int)a == par){
                continue;
            }
            sum += countPotions((int)a,cur,graph, modpots);
        }
        System.out.println(sum + " " + modpots[cur]);
        sum += modpots[cur];
        
        return Math.min(sum,numleaves[cur]);
    }
    public static int[] numleaves;
    public static int countleaves(int cur, int par, ArrayList[] graph){
        if ((graph[cur].size() == 1 && (int)graph[cur].get(0) == par) || graph[cur].size() == 0){
            numleaves[cur] = 1;
            return 1;
        }
        int sum = 0;
        for (Object a : graph[cur]){
            if ((int)a == par){
                continue;
            }
            sum += countleaves((int)a,cur,graph);
        }
        numleaves[cur] = sum;
        return sum;
    }
}