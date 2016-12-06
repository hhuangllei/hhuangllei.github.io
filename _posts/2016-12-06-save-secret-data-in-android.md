---
layout: post
title: Android app保存加密数据
categories: [coding, Java, Android]
modify_date: 2016-12-06 11:00:00 +0800
---

### 1. 流程总述  
生成密钥（如何安全保存？）  
数据加密，加密用户名、密码等敏感数据  
数据存储  
数据解密  

### 2. Android数据存储方式  
Files、SharedPreferences、Content Providers、SQLite、Network  

SharedPreferences  
保存的数据以xml形式存储在/data/data/<pakage name>/shared_prefs。  
getDefaultSharedPreferences  
getSharedPreferences  

* 写入数据  

```Java
SharedPreferences settings = mContext.getSharedPreferences(name, Context.MODE_PRIVATE);
SharedPreferences.Editor editor = settings.edit();
editor.putString(key, value);
editor.commit();
```

* 读取数据  

```Java
SharedPreferences settings = mContext.getSharedPreferences(name, Context.MODE_PRIVATE);
String value = settings.getString(key, defValue);
```


### 3. 数据编码加密  

```java
import java.security.Key;

import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;

public class MainClass {
  public static void main(String[] args) throws Exception {
    KeyGenerator keyGenerator = KeyGenerator.getInstance("DESede");
    keyGenerator.init(168);
    Key key = keyGenerator.generateKey();

    Cipher cipher = Cipher.getInstance("DESede/ECB/PKCS5Padding");
    cipher.init(Cipher.ENCRYPT_MODE, key);

    byte[] ciphertext = cipher.doFinal("text".getBytes("UTF8"));

    for (int i = 0; i < ciphertext.length; i++) {
      System.out.print(ciphertext[i] + " ");
    }

    cipher.init(Cipher.DECRYPT_MODE, key);

    byte[] decryptedText = cipher.doFinal(ciphertext);

    System.out.println(new String(decryptedText, "UTF8"));
  }
}
//-71 -27 -10 -67 -24 -37 -79 70 text (随机key，结果存在差异)
```

密钥长度要求，需要16bytes或者24bytes，所以需要对自己设置的密钥进行编码得到符合长度要求的密钥，比如使用MD5加密。  
`java.security.InvalidKeyException: key size must be 128 or 192 bits`  

```java
public static byte[] GenKeyBytes(String strKey) {
    byte[] keyBytes = null;

    try {
        MessageDigest md = MessageDigest.getInstance("MD5");
        md.update(strKey.getBytes());
        keyBytes = md.digest(); // 16bytes
    } catch (Exception e) {
        throw new Error("Failed to generate MD5 : " + e.getMessage());
    }

    // 24bytes
    int start = keyBytes.length;
    byte[] keyBytes24 = new byte[24];
    for (int i = 0; i < start; i++) {
            keyBytes24[i] = keyBytes[i];
    }
    for (int i = start; i < 24; i++) {
        keyBytes24[i] = keyBytes[i - start];
    }

    return keyBytes24;
}
```



* [Android 对用户名密码进行加密操作存储在本地](http://blog.csdn.net/w18756901575/article/details/51373693)  
* [移动App该如何保存用户密码](http://blog.csdn.net/hengyunabc/article/details/34623957)  
* [使用Shared Preferences方式存储数据](http://www.cnblogs.com/menlsh/archive/2013/04/07/3006510.html)  
* [安卓getSharedPreferences 与 getPreferences 与getDefaultSharedPreferences的区别](http://blog.csdn.net/w47_csdn/article/details/51766401)  
* [using the name DESede rather than TripleDES : DESede](http://www.java2s.com/Tutorial/Java/0490__Security/usingthenameDESederatherthanTripleDES.htm)  
* [java的3DES加密/解密](http://blog.csdn.net/jingdian14/article/details/7800524)  