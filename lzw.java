package lzw;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class lzw{
    public static void main(String[] args) {

        Scanner read = new Scanner(System.in);

        String text = read.next();

        read.close();

        int size = 256;
        Map<String, Integer> dictionary = new HashMap<>();
        for (int i = 0; i<size; i++){
            dictionary.put(String.valueOf((char) i),i);
        }

        String foundChars = "";
        List<String> result = new ArrayList<>();

        for (char symbol : text.toCharArray()){
            String charsToAdd = foundChars + symbol;

            System.out.println("");
            System.out.println("found chars: "+foundChars);
            System.out.println("symbol: "+ symbol);
            System.out.println("chars to add: "+charsToAdd);

            if(dictionary.containsKey(charsToAdd)){
                foundChars = charsToAdd;
            }else{
                result.add(foundChars);
                dictionary.put(charsToAdd, size++);
                foundChars = String.valueOf(symbol);
            }
        }

        System.out.println("");
        System.out.println("ending found char: " + foundChars);

        if (!foundChars.isEmpty()){
            result.add(foundChars);
        }

        System.out.println(result);
    }


}