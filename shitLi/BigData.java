import java.io.*;

public class BigData {

    /*public static void main(String[] args) {
        String filePath = "/home/yang/Desktop/13301104001";
        String encoding = "GBK";
        String outFilePath = "/home/yang/Desktop/out";

        try {
            File file = new File(filePath);
            File outFile = new File(outFilePath);
            if (file.isFile() && file.exists()) {
                InputStreamReader in = new InputStreamReader(new FileInputStream(file), encoding);
                BufferedReader buff = new BufferedReader(in);
                OutputStream outPut = new FileOutputStream(outFile);
                String line;
                while ((line = buff.readLine()) != null) {
                    String words[] = line.split(",");
                    if (Integer.parseInt(words[8]) <= 90) {
                        byte data[] = line.getBytes();
                        outPut.write(data);
                        outPut.write("\n".getBytes()); //\r\n是win换行符，根据不同情况更改
                    }
                }
                in.close();
                buff.close();
                outPut.close();
            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }*/

    private static final double EARTH_RADIUS = 6378137;

    public static void main(String[] args) {
        String inFilePath = "/home/yang/Desktop/13301104001";
        String encoding = "UTF8";
        String outFilePath = "/home/yang/Desktop/out";
        File inFile;
        File outFile;
        InputStreamReader in = null;
        BufferedReader buff = null;
        OutputStream out = null;

        inFile = new File(inFilePath);
        outFile = new File(outFilePath);

        if (inFile.isFile() && inFile.exists()) {
            try {
                in = new InputStreamReader(new FileInputStream(inFile), encoding);
                buff = new BufferedReader(in);
                out = new FileOutputStream(outFile);

                String line1 = buff.readLine();
                String line2 = buff.readLine();
                while (line1 != null && line2 != null) {
                    String words1[] = line1.split(",");
                    String words2[] = line2.split(",");

                    //转化为Double
                    double num11 = Double.parseDouble(words1[4]);
                    double num12 = Double.parseDouble(words1[5]);
                    double num21 = Double.parseDouble(words2[4]);
                    double num22 = Double.parseDouble(words2[5]);

                    if (getDistance(num11, num12, num21, num22) < 2000) {//小于2000全写
                        byte data[] = (line1 + "\n").getBytes();
                        out.write(data);
                        data = (line2 + "\n").getBytes();
                        out.write(data);
                    } else if (getDistance(num11, num12, num21, num22) > 2000) {//大于2000只写第一个
                        byte data[] = (line1 + "\n").getBytes();
                        out.write(data);
                    }

                    //递进
                    line1 = line2;
                    line2 = buff.readLine();
                }

            } catch (UnsupportedEncodingException e) {
                e.printStackTrace();
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        try {
            in.close();
            buff.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        
    }

    private static double rad(double d) {
        return d * Math.PI / 180.0;
    }

    public static double getDistance(double lng1, double lat1, double lng2, double lat2) {
        double radLat1 = rad(lat1);
        double radLat2 = rad(lat2);
        double a = radLat1 - radLat2;
        double b = rad(lng1) - rad(lng2);
        double s = 2 * Math.asin(Math.sqrt(Math.pow(Math.sin(a / 2), 2)
                + Math.cos(radLat1) * Math.cos(radLat2) * Math.pow(Math.sin(b / 2), 2)));
        s = s * EARTH_RADIUS;
        s = Math.round(s * 10000) / 10000;
        return s;

    }
}