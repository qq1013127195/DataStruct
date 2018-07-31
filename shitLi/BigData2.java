import java.io.*;

public class BigData2 {
    public static void main(String[] args) {
        String inFilePath = "/home/yang/Desktop/13301104001";
        String outFilePath = "/home/yang/Desktop/out";
        String encoding = "UTF8";

        File inFile = new File(inFilePath);
        File outFile = new File(outFilePath);
        InputStreamReader in = null;
        BufferedReader buff = null;
        OutputStream out = null;

        try {
            in = new InputStreamReader(new FileInputStream(inFile), encoding);
            buff = new BufferedReader(in);
            out = new FileOutputStream(outFile);

            if (inFile.exists() && inFile.isFile()) {
                String line = null;
                while ((line = buff.readLine()) != null) {
                    String words[] = line.split(",");
                    line = words[2];
                    for (int i = 3; i < words.length; i++) {
                        line = line + "," + words[i];
                    }
                    out.write((line + "\n").getBytes());
                }
            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            in.close();
            buff.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
