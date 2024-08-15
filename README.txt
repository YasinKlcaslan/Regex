Regex Ayrıştırıcısı

Giriş
Regex Ayrıştırıcısı, kullanıcıdan bir regex deseni ve bir metin girişi alan ve regex deseni içindeki belirli meta karakterleri işleyen bir Python betiğidir. Bu betik ?, |, *, +, {}, [], (), ^, $, . içerir. . gibi yaygın regex meta karakterlerini tanır ve işler.

Nasıl kullanılır?
Desen ve metni parser(pattern, text) işlevini kullanarak parametre olarak gönderin.
Desen içindeki meta karakterlere göre uygun işlevler otomatik olarak çağrılacaktır.
Eşleşmeler konsola yazdırılacaktır.

Örnek:

pattern = "a?b"
text = "ab abb aabb aaabb"
parser(pattern, text)
Bu örnekte, ? Meta karakterle işaretlenen "a" karakterinin var olup olmadığını kontrol ediyoruz.

Desteklenen Meta Karakterler
?: Sorgu işareti, önceki karakterin isteğe bağlı olduğunu gösterir. |: Dikey çubuk iki alternatif deseni birleştirir.
*: Yıldız işareti, önceki karakterin sıfır veya daha fazla oluşumunu gösterir.
+: Artı işareti, önceki karakterin bir veya daha fazla oluşumunu gösterir.
{}: Kıvrımlı parantezler, belirli bir aralıktaki tekrarları gösterir.
[]: Köşeli parantezler, belirli bir karakter kümesini gösterir.
(): Yuvarlak parantezler, gruplandırmayı ve alt ifadeleri gösterir.
^: İşaret, bir deseni metnin başlangıcıyla eşleştirir.
$: Dolar işareti, bir deseni metnin sonuyla eşleştirir.
.: Nokta sembolü, herhangi bir tek karakteri temsil eder.
