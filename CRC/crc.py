# -*- coding: utf-8 -*-
# Bu üstteki yorum satırlarının kabul edilmesi için koda özel olarak eklenmiştir.
# Bunu eklemeyince verdiği hata: The problem is that your code is trying to use the 
# ASCII encoding, but the pound symbol is not an ASCII character. 
# Try using UTF-8 encoding

# Python'daki struct modülü, dizeler ve sayılar gibi yerel Python veri
# türlerini bir bayt dizesine dönüştürmek için kullanılır ve bunun tersi
# de geçerlidir. Python sys modülü, Python Çalışma Zamanı Ortamının farklı
# bölümlerini işlemek için kullanılan işlevler ve değişkenler sağlar.
# Re kütüphanemizde Python'daki normal ifade veya RegEx, 
# RE (RE'ler, regexes veya regex kalıbı) re modülü aracılığıyla 
# içe aktarılır olarak belirtilir
import struct
import sys
import re 

# Burada ilk değerimiz input değerimiz, diğeri divisor değerimizdir.
deger1="1001100"
deger2="1101"

# Bu fonksiyonun amacı deger1 ve deger2 değerlerini polinom şeklinde gösterebilmektir.
# Bu iki değer içinde sonradan kullanılacaktır.
def polinomuGoster(a):
	str1 = ""
	bitsayi = len(a)
	for x in range (0,bitsayi-2):
		if (a[x] == '1'):
			if (len(str1)==0):
				str1 +="x**"+str(bitsayi-x-1)	
			else: 
				str1 +="+x**"+str(bitsayi-x-1)

	if (a[bitsayi-2] == '1'):
		if (len(str1)==0):
			str1 +="x"
		else:
			str1 +="+x"

	if (a[bitsayi-1] == '1'):
		str1 +="+1"

	print str1
	
# Bu fonksiyonumuz değerleri bir listeye eklemektedir.
# Bunun için bir dizi ve diziye ekleme işlemi yapan append() fonksiyonunu kullanmaktadır.
def ListeyeEkle(x):
	l = []
	for i in range (0,len(x)):
		l.append(int(x[i]))
	return (l)

# Bu fonksiyon buna parametre olarak gönderilen değeri string’e
# çeviriyor ve bize return değeri olarak sunmaktadır.
def toString(x):
	str1 =""
	for i in range (0,len(x)):
		str1+=str(x[i])
	return (str1)

# Şimdi asıl önemli kısma girmekteyiz. Burada bölme işlemini yapacağız. 
# Verileri ilk başta listeye aktarıyoruz ve deger1 değerini calisma adlı 
# parametreye string değer olarak gönderiyoruz.
def bolmeIslemi(deger1,deger2):
	a = ListeyeEkle(deger1)
	b = ListeyeEkle(deger2)
	calisma=toString(deger1)+"\n"

	res=""
	boslukEkle=""

	# Burada kaynak taramasında anlatmış olduğumuz bölme işlemini yapmaktayız. 
	# Yaptığımız işlemlerin böyle bu şekilde karmaşık olmasının sebebi bölme 
	# olayını terminalde tamamen gösterilebilmesini sağlamaktır. Çıktı kısmında 
	# örneğini görebileceksiniz. While döngüsünde a değerimiz b değerimizden 
	# büyük oldukça devam etmektedir ve küçük olduğu durumda ise bölme işlemimiz 
	# son bulmaktadır.
	while len(b) <= len(a) and a:
    		if a[0] == 1:
        		del a[0]
        		for j in range(len(b)-1):
            			a[j] ^= b[j+1]
        		if (len(a)>0):
				calisma +=boslukEkle+toString(b)+"\n"
				calisma +=boslukEkle+"-" * (len(b))+"\n"
				boslukEkle+=" "
				calisma +=boslukEkle+toString(a)+"\n"
				res+= "1"

		else:
        		del a[0]
			calisma +=boslukEkle+"0" * (len(b))+"\n"
			calisma +=boslukEkle+"-" * (len(b))+"\n"
			boslukEkle+=" "
			calisma +=boslukEkle+toString(a)+"\n"

        		res+="0"

	# Burada çıktılarımızı göstermekteyiz. İlk başta result değerimiz,
	# sonra kalan değerimiz bulunmaktadır. Çalışma kısmında bölüm
	# olayının nasıl yapıldığı bulunmaktadır.
	print "Çıktı: \t",res
	print "Kalan: \t",toString(a)

	print "Çalışma: \t\n\n",res.rjust(len(deger1)),"\n",
	print "-" * (len(deger1)),"\n",calisma

	return toString(a)

# Burada artık main işlemler yapılmaktadır. Değerleri gösterme işlemi yapıldıktan 
# sonra polinom halinde gösterimler yapılmaktadır.
print "İkili Form:",deger1,", Bölen sayısı: ",deger2
print ""
polinomuGoster(deger1)
polinomuGoster(deger2)

# Burada 0 değerleri deger1’e eklenmektedir.
strSifir=""
strSifir = strSifir.zfill(len(deger2)-1)
deger3=deger1+strSifir

# Burada 0 eklenmiş hali gösterilmektedir.
print ""
print "İkili form (0'lar eklendi): ",deger3,"Bölen sayı: ",deger2

# Bu kısımda ise bizim için önemli olan bölüm fonksiyonu çalışmıştır
# ve fonksiyonun çalışması bittikten sonra çıktı değerini bize sunmaktadır.
res=bolmeIslemi(deger3,deger2)
print "Gönderilen değer:",deger1+res
print "Şimdi Doğru gönderim hatalı mı diye bakacağız şimdi."

#Hatalı mı değil mi diye kontrol ediyoruz burada
yeniSayi = deger1+res
yeniSayi = yeniSayi

#Tekrardan bir bölme işlemi yapılması gerekiyor yeni sayıyla
#Bu şekilde çıktıdan anlamış olacağız hatalı mı değil mi diye.
res= bolmeIslemi(yeniSayi, deger2)
print "Hata kodumuz:", res

#Burada sonucumuzda 1 olup olmadığına bakıyoruz.
found = re.search("1", res)

if(found):
	print "Hatalı gönderim yapıldı!"
else:
	print "Doğru gönderim yapıldı!"

# Bu şekilde çalışmalarını bitirmektedir. Bu kod python 2.7 ile sorunsuz bir
# şekilde çalışmaktadır.