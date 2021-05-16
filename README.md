# SistemProgramlama
Proje Ödevi





Muhammet Sağlam              B191210304
Harun Aydemir                B191210308
Emre Koç	                   G191210383
Numan Güngör                 B191210307


 
Muhammet Sağlam

Proje Yöneticisi Github’da projenin oluşturulması, grup proje toplantıları ve bunların raporlanması,
proje raporlarının takip edilip iletilmesi  gibi sorumluları gerçekleştirdim…



Harun Aydemir

Json formatında kilit dosyasının okunması  ve kodlarınnı hazırladı.



Emre Koç

Encode ve decode işlemlerinin yapılması 



Numan Güngör 


Deployment sorumlusu (Makefile ve argümanlar, programlama standartları), dokümantasyon ve düzen 







Derleme Süreci 

1.	Öncelikli olarak kütüphaneyi linux ortamında kullanabilmek için , kendi işletim sistemime göre derlemem gerekiyordu, kütüphaneyi indirdikten sonra içinde bulunan Makefile dosyası sayesinde kendimin kullanabileceği bir kütüphaneyi , kendi işletim sistemime özel olarak derledim.
2.	Ağaç oluşturmak için JRB enc = make_jrb(); yazmak yeterli oluyor.
3.	Ağacı anahtar-değer ilişkisinde kullanabilmek için değer eklerken farklı bir komut kullanmam gerekti -> jrb_insert_gen(kilitTree, new_jval_s(gelenKelime), new_jval_i(deger), revcomp)
a.	Ilk parameter hangi ağaca ekleme yapıcaz
b.	Ikinci parameter anahtar
c.	Ucuncu parameter deger
d.	Son parameter ise red-black tree de ağaca yeni bir veri eklerken diğer düğümler ile nasıl karşılaştırma yapılacağı ile ilgili bir metod
4.	Ağaçtan veri çekmek için iki yöntem kullandım çünkü bir çalıştı bir çalışmadı bende garanti olsun diye 2 yöntemide kullandım
a.	jrb_find_str
b.	jrb_find_gen
i.	bu iki kütüphaneden gelen değerleri eğer int alam gerekiyorsa val.i eğer string ise val.s olarak geçtim

Derleme Sürecinde Kütüphane Kullanımı
1.	Program ilk olarak red-black tree ‘yi oluşturarak başlıyor eğer enc yapılacak ise kilitTree , dec yapılacak ise decKilitTree nesnesini kullanıyor
a.	Ikisini arasındaki fark birinde anahtar olan değer , diğerinde değer olan anahtar, çünkü şifrelerden anahtarın kelime olması lazım oysa şifre açarken anahtarın kelimenin Huffman kodu karşılığı olması gerekiyor
2.	Ikinci iş dosyaOku metoduyla verilen dosyadaki kelimeleri tek tek alıp , ağaçtan karşılığını alarak şifrelemek yada şifreyi açmak



Karşılaştığım hatalar ,zorluklar Çalışmayan kısımlar


•	Json nasıl okuyacağımı bilemeğim için kendime özel bir metod yazdım, eğer kelime okuyosam kelimenin ‘a’ ile ‘z’ ve ‘A’ ile ‘Z’ arasında olmasına dikkat ettiğim bunun dışındaki karakterlere pass geçtim, bu sayılar içinde aynı şekilde yapıldı.
•	Output oluştururken yazmam gerekenleri bir değişkende tutmak yerine her bulduğum değişkeni dosyaya append ettim



