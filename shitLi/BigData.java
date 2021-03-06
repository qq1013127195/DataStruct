import java.io.*;
import java.util.ArrayList;

public class BigData {

    public static void main(String[] args) {
        String inFolderPath = "/home/yang/Desktop/zzz";//你存放文件的目录(zzz下含有此格式所有文件)
        String encoding = "UTF8";
        String outFilePath = "/home/yang/Desktop/out";//你要输出到的文件(out是一个文件，不是一个文件夹，也就是说艘有数据输出到同一个文件里)
        ArrayList<String> files = new ArrayList<>();

        File inFolder;
        File outFile;
        InputStreamReader in = null;
        BufferedReader buff = null;
        OutputStream out = null;

        inFolder = new File(inFolderPath);
        outFile = new File(outFilePath);

        File[] inFiles = inFolder.listFiles();

        for (int i = 0; i < inFiles.length; i++) {
            try {
                in = new InputStreamReader(new FileInputStream(inFiles[i]), encoding);
                buff = new BufferedReader(in);
                out = new FileOutputStream(outFile, true);

                if (inFiles[i].isFile() && inFiles[i].exists()) {

                    boolean bool = false;//判断上一个是否输出了两个

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

                        if (Integer.parseInt(words1[8]) <= 90) {
                            if (getDistance(num11, num12, num21, num22) < 2000) {//小于2000全写
                                if (bool) { //如果上一次输出了两行，此次再输出line1就重复了（这一行的line1等于上一次的line2）
                                    byte data[] = (line2 + "\n").getBytes();
                                    out.write(data);
                                } else {
                                    byte data[] = (line1 + "\n").getBytes();
                                    out.write(data);
                                    data = (line2 + "\n").getBytes();
                                    out.write(data);
                                }
                                bool = true;
                            } else if (getDistance(num11, num12, num21, num22) >= 2000) {//大于2000只写第一个
                                if (!bool) { //和上面同理
                                    byte data[] = (line1 + "\n").getBytes();
                                    out.write(data);
                                }
                                bool = false;
                            }

                        } else {
                            bool = false;
                        }

                        //递进
                        line1 = line2;
                        line2 = buff.readLine();
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

    private static final double EARTH_RADIUS = 6378137;

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