def QuestionMark(pattern, text):
    # Parçalanmış desenler için boş bir liste başlatır.
    splitPattern = []
    # Eşleşmeleri saklamak için boş bir liste başlatır.
    matches = []
    # Desenin uzunluğunu alır.
    lenPattern = len(pattern)
    
    # Deseni incelemek için döngü oluşturur.
    for i in range(lenPattern - 1):
        # Eğer 'pattern' içinde soru işareti ('?') varsa
        if pattern[i] == "?":
            # Soru işaretinden önceki kısmı 'splitPattern'e ekler.
            splitPattern.append(pattern[:i - 1])
            # Soru işaretinden sonraki kısmı 'splitPattern'e ekler.
            splitPattern.append(pattern[i + 1:])
            # Bölümleri birleştirir ve 'matches' listesine ekler.
            adder = "".join(splitPattern)
            matches.append(adder)

            # Listeyi temizleyerek baştan başlar.
            splitPattern = []
            # Soru işaretinden hemen önceki kısmı 'splitPattern'e ekler.
            splitPattern.append(pattern[:i])
            # Soru işaretinden hemen sonraki kısmı 'splitPattern'e ekler.
            splitPattern.append(pattern[i + 1:])
            # Bölümleri birleştirir ve 'matches' listesine ekler.
            adder = "".join(splitPattern)
            matches.append(adder)

    # 'matches' listesindeki parçaları kontrol etmek için döngü.
    i = 0
    while i < len(matches):
        # Metin içinde mevcut parçayı kontrol eder ve bulursa yazdırır.
        if matches[i] in text:
            print(matches[i])
        # Bir sonraki parçaya geçer.
        i += 1

def OR(pattern, text):
    # Deseni '|' ile bölmek için boş bir liste tanımlıyoruz.
    splitPattern = []
    # Eşleşmeleri saklamak için boş bir liste tanımlıyoruz.
    matches = []
    # Desenin uzunluğunu hesaplıyoruz.
    lenPattern = len(pattern)

    # Desen içinde '|' olup olmadığını kontrol ediyoruz ve varsa bölüyoruz.
    for i in range(lenPattern - 1):
        if pattern[i] == "|":
            splitPattern = pattern.split("|")

    # Bölünmüş desenin her bir parçasını 'matches' listesine ekliyoruz.
    for i in range(len(splitPattern)):
        matches.append(splitPattern[i])

    # 'matches' listesini döngüyle kontrol ederek eşleşmeleri buluyoruz.
    i = 0
    while i < len(matches):
        # Metin içinde 'matches' listesindeki parçanın bulunup bulunmadığını kontrol ediyoruz.
        if matches[i] in text:
            # Eşleşme bulunduğunda, bu parçayı yazdırıyoruz.
            print(matches[i])
        # Bir sonraki elemanı kontrol etmek için ilerliyoruz.
        i += 1

def PlusSign(pattern, text):
    # '+' işaretini baz alarak deseni parçalara ayırırız.
    splitPattern = pattern.split("+")
    start_sequence = splitPattern[0]  # '+' işaretinden önceki kısım
    endSequence = splitPattern[1]  # '+' işaretinden sonraki kısım

    matches = []
    # Metinde eşleşmeleri bulmak için indeks kullanırız.
    i = 0
    while i < len(text):
        # Metnin başlangıcı artı işaretinden önceki kısımla eşleşiyor mu?
        if text[i:i+len(start_sequence)] == start_sequence:
            # '+' işareti anlamındaki ardışık karakterleri kontrol ederiz.
            j = i + len(start_sequence)
            while j < len(text) and text[j] == start_sequence[-1]:
                j += 1
            # '+' işaretinden sonraki kısmı kontrol ederiz.
            if text[j:j+len(endSequence)] == endSequence:
                # Tam bir eşleşme bulunduğunda, bu kısmı yazdırırız.
                matches.append(text[i:j + len(endSequence)])
                # Bir sonraki arama için indeksi ayarlayarak devam ederiz.
                i = j + len(endSequence) - 1
            else:
                i += 1
        else:
            i += 1
    for i in matches:
        print(i)

def StarSign(pattern, text):
    # '*' işaretini baz alarak deseni parçalara ayırırız.
    splitPattern = pattern.split("*")
    startSequence = splitPattern[0]  # '*' işaretinden önceki kısım
    endSequence = splitPattern[1]  # '*' işaretinden sonraki kısım
    beforeStar = startSequence[-1] # '*' işaretinden önceki index
    
    matches = []
    firstMatch = (startSequence + endSequence).split(beforeStar)
    firstMatch = "".join(firstMatch)
    matches.append(firstMatch) #'*' işareti olmayan durumun array'e eklenmesi
    
    i = 0
    while i < len(text):
        # Metnin başlangıcı start_sequence ile eşleşiyor mu?
        if text[i:i + len(startSequence)] == startSequence:
            # Başlangıç sekansı ile eşleşme bulduğumuzda, yıldız işaretinden sonraki karakterleri kontrol ederiz
            j = i + len(startSequence)
            while j < len(text) and text[j] == startSequence[-1]:
                j += 1  # Yıldızdan sonra gelen karakterleri kontrol ediyoruz
            # Bitiş sekansı ile eşleşiyor mu?
            if text[j:j + len(endSequence)] == endSequence:
                # Eşleşmeyi bulduğumuzda, matches dizisine ekleriz
                matches.append(text[i:j + len(endSequence)])
                # Bir sonraki kontrol için indeksi güncelleriz
                i = j + len(endSequence)
            else:
                i += 1  # Eşleşme yoksa, bir adım ilerleriz
        else:
            i += 1  # Başlangıç sekansı ile eşleşmezse, bir adım ilerleriz
    
    for i in matches:
        print(i)

def CurlyBracket(pattern,text):
    matches = []

    # Text'i boşluklara göre ayırırız.
    textElements = text.split()

    # Start ve end sekanslarını ayırırız
    if '{' in pattern and '}' in pattern:
        # Deseni {} arasındaki kısmı ayırmak için kullanılır
        startEndSequence = pattern.split('}')
        startSequence = startEndSequence[0].split('{')[0]
        repeatValues = startEndSequence[0].split('{')[1]

        # Virgülle ayırdıktan sonra değerleri alırız
        rangeValues = repeatValues.split(',')

        # Aralık belirtilmişse
        if len(rangeValues) == 2:
            start_value = int(rangeValues[0])
            # Eğer aralığın sonu boşsa, varsayılan bir maksimum tekrar belirleriz
            if rangeValues[1] == '':
                max_repeat = 20
                for i in range(start_value, max_repeat + 1):
                    new_pattern = startSequence * i
                    if new_pattern in textElements:
                        matches.append(new_pattern)
            else:
                end_value = int(rangeValues[1])
                # Aralığın başlangıcından bitişine kadar tekrarlama yaparız
                for i in range(start_value, end_value + 1):
                    new_pattern = startSequence * i
                    if new_pattern in textElements:
                        matches.append(new_pattern)

        elif len(rangeValues) == 1:
            # Belirtilen tek bir tekrar varsa
            new_pattern = startSequence * int(rangeValues[0])
            if new_pattern in textElements:
                matches.append(new_pattern)
    
    print(matches)

def SquareBracket(pattern, text):
    # Desende kare parantez içindeki deseni ayıklayın
    insideBrackets = pattern.split("[")[1].split("]")[0]
    # Kare parantezlerin dışındaki başlangıç ve bitiş desenlerini alın
    startPattern = pattern.split("[")[0]
    endPattern = pattern.split("]")[1]

    # Metni kelimelere ayırın
    splittedText = text.split()
    # Eşleşmeleri kaydetmek için liste oluşturun
    matches = []

    # Metin içindeki kelimeler arasında kontrol yapın
    for word in splittedText:
        # Başlangıç ve bitiş desenlerine uyan kelimeleri kontrol edin
        if word.startswith(startPattern) and word.endswith(endPattern):
            # Kare parantez içindeki desene uygun olup olmadığını kontrol edin
            if insideBrackets in word:
                matches.append(word)

    # Eşleşmeleri yazdırın
    print(matches)

def Bracket(pattern, text):
    # Yuvarlak parantez içindeki ifadeleri toplamak için liste
    matches = []
    # Parantezler arasında olup olmadığını kontrol etmek için bayrak
    inParentheses = False
    # Parantez içindeki karakterleri toplamak için değişken
    temp = ""

    splittedText = text.split() 

    # Deseni karakter bazında döngüyle tarayın
    for char in pattern:
        if char == '(':  # Parantez başlarsa, bayrağı açın ve temizleyin
            inParentheses = True
            temp = ""  # Temizleyin
        elif char == ')':  # Parantez kapanırsa, bayrağı kapatın ve sonucu ekleyin
            if inParentheses:
                matches.append(temp)
                inParentheses = False
        elif inParentheses:  # Parantez içindeyken karakterleri toplayın
            temp += char

    # Elde edilen ifadeleri metin içinde kontrol edin ve eşleşmeleri yazdırın
    for result in matches:
        if result in splittedText:
            print(matches)

def PowerSign(pattern, text):
    # 'text' kelimelerini ayırmak için boşlukla bölüyoruz
    splittedText = text.split()
    # 'pattern' içinde '^' karakterinden sonraki kısmı alıyoruz
    start_pattern = pattern.split("^")[1]
    # Eşleşen kelimeleri tutmak için liste oluşturuyoruz
    matches = []

    # Tüm kelimeleri kontrol ediyoruz
    for word in splittedText:
        # Eğer kelime başlangıç paternine uyuyorsa, listeye ekliyoruz
        if word.startswith(start_pattern):
            matches.append(word)
    
    # Eşleşen kelimeleri yazdırıyoruz
    print(matches)

def DollarSign(pattern, text):
    # Metindeki kelimeleri ayırmak için boşlukla bölüyoruz
    splittedText = text.split()
    # 'pattern' içindeki '$' işaretinden önceki kısmı alıyoruz
    end_pattern = pattern.split("$")[0]
    # Eşleşen kelimeleri tutmak için liste oluşturuyoruz
    matches = []

    # Metindeki her kelimeyi kontrol ediyoruz
    for word in splittedText:
        # Eğer kelime bitiş paternine uyuyorsa, listeye ekliyoruz
        if word.endswith(end_pattern):
            matches.append(word)
    
    # Eşleşen kelimeleri yazdırıyoruz
    print(matches)

def PointSign(pattern, text):
    # Metindeki kelimeleri boşluklarla ayırıyoruz
    words = text.split()

    # 'pattern' içindeki '.' işaretine göre bölüyoruz
    split_pattern = pattern.split(".")
    start_pattern = split_pattern[0]  # '.' işaretinden önceki kısım
    end_pattern = split_pattern[1]  # '.' işaretinden sonraki kısım

    matches = []

    # Tüm kelimeleri kontrol ediyoruz
    for word in words:
        # Başlangıç ve bitiş desenlerine uyan ve uzunluğu aynı olan kelimeleri seçiyoruz
        if word.startswith(start_pattern) and word.endswith(end_pattern) and len(word) == len(pattern):
            matches.append(word)

    # Eşleşen kelimeleri yazdırıyoruz
    print(matches)

def parser(pattern, text):
    # Desendeki her bir karakteri kontrol ederiz
    for i in pattern:
        # Eğer karakter metakarakterler listesinde ise uygun fonksiyonu çağırırız
        if i in metacharacters:
            if i == "?":
                QuestionMark(pattern, text)
            elif i == "|":
                OR(pattern, text)
            elif i == "*":
                StarSign(pattern, text)
            elif i == "+":
                PlusSign(pattern, text)
            elif i == "{":
                CurlyBracket(pattern, text)
            elif i == "[":
                SquareBracket(pattern, text)
            elif i == "(":
                Bracket(pattern, text)
            elif i == "^":
                PowerSign(pattern, text)
            elif i == "$":
                DollarSign(pattern, text)
            elif i == ".":
                PointSign(pattern, text)

pattern =input("Lütfen Pattern giriniz: ")
text =input("Lütfen Text giriniz: ")

# Regex metacharacters listesi
metacharacters = ["?", ".", "*", "+", "^", "$", "|", "(", ")", "[", "]", "{", "}", "\\"]

parser(pattern,text)