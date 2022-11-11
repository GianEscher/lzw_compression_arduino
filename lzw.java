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
        List<Integer> result = new ArrayList<>();

        for (char symbol : text.toCharArray()){
            String charsToAdd = foundChars + symbol;

            System.out.println("");
            System.out.println("found chars: "+foundChars);
            System.out.println("symbol: "+ symbol);
            System.out.println("chars to add: "+charsToAdd);

            if(dictionary.containsKey(charsToAdd)){
                foundChars = charsToAdd;
            }else{
                result.add(dictionary.get(foundChars));
                dictionary.put(charsToAdd, size++);
                foundChars = String.valueOf(symbol);
            }
        }

        System.out.println("");
        System.out.println("ending found char: " + foundChars);

        if (!foundChars.isEmpty()){
            result.add(dictionary.get(foundChars));
        }

        System.out.println(result);

        System.out.println("");
        System.out.println("decoded result: " + decoder(result));

        
    }

    public static String decoder(List<Integer> encodedText){

        int size = 256;
        Map<Integer, String> dictionary = new HashMap<>();
        for (int i = 0; i<size; i++){
            dictionary.put(i, String.valueOf((char) i));
        }

        String characters = String.valueOf((char) encodedText.remove(0).intValue());
        StringBuilder result = new StringBuilder(characters);
        for (int code : encodedText){
            String entry;
            if(dictionary.containsKey(code)){
                entry = dictionary.get(code);
            }else{
                entry = characters + characters.charAt(0);
            }
            result.append(entry);
            dictionary.put(size++, characters + entry.charAt(0));

            System.out.println("");
            System.out.println("entry: "+entry);
            System.out.println("dictionary entry: "+ characters + entry.charAt(0));
            System.out.println("prev characters: "+characters);

            characters = entry;
        }
        return result.toString();
    }


}