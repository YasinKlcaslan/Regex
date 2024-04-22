#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

void QuestionMark(const std::string &pattern, const std::string &text)
{
    // Deseni bölmek için boş bir vektör oluştur
    std::vector<std::string> splitPattern;
    // Eşleşmeleri saklamak için bir vektör oluştur
    std::vector<std::string> matches;
    // Desenin uzunluğunu al
    size_t lenPattern = pattern.size();

    // Deseni incelemek için döngü oluştur
    for (size_t i = 0; i < lenPattern - 1; ++i)
    {
        // Eğer desen içinde soru işareti varsa
        if (pattern[i] == '?')
        {
            // Soru işaretinin öncesini ekle
            splitPattern.push_back(pattern.substr(0, i - 1));
            // Soru işaretinin sonrasını ekle
            splitPattern.push_back(pattern.substr(i + 1));

            // Bölümleri birleştir ve eşleşmelere ekle
            std::string adder = "";
            for (const auto &part : splitPattern)
            {
                adder += part;
            }
            matches.push_back(adder);

            // SplitPattern'i temizle ve yeniden başla
            splitPattern.clear();

            // Soru işaretinin hemen öncesini ve sonrasını ekle
            splitPattern.push_back(pattern.substr(0, i));
            splitPattern.push_back(pattern.substr(i + 1));

            // Bölümleri birleştir ve eşleşmelere ekle
            adder = "";
            for (const auto &part : splitPattern)
            {
                adder += part;
            }
            matches.push_back(adder);
        }
    }

    // Eşleşmeleri kontrol etmek için bir döngü
    for (size_t i = 0; i < matches.size(); ++i)
    {
        // Eğer metin içinde eşleşme varsa, yazdır
        if (text.find(matches[i]) != std::string::npos)
        {
            std::cout << matches[i] << std::endl;
        }
    }
}

void OR(const std::string &pattern, const std::string &text)
{
    // Deseni '|' sembolü ile bölecek bir vektör oluştur.
    std::vector<std::string> splitPattern;
    // Eşleşmeleri saklamak için bir vektör oluştur.
    std::vector<std::string> matches;
    // Desenin uzunluğunu al.
    size_t lenPattern = pattern.size();

    // Deseni '|' sembolü ile böler ve 'splitPattern' içine ekler.
    std::istringstream stream(pattern);
    std::string segment;
    while (std::getline(stream, segment, '|'))
    {
        splitPattern.push_back(segment);
    }

    // 'splitPattern' içindeki her bir segmenti 'matches' listesine ekler.
    for (const auto &part : splitPattern)
    {
        matches.push_back(part);
    }

    // Eşleşmeleri kontrol etmek için bir döngü.
    for (const auto &match : matches)
    {
        // Metin içinde eşleşmeyi kontrol eder.
        if (text.find(match) != std::string::npos)
        {
            // Eğer eşleşme varsa, konsola yazdırır.
            std::cout << match << std::endl;
        }
    }
}

void PlusSign(const std::string &pattern, const std::string &text)
{
    // '+' işaretine göre deseni parçalara ayır.
    size_t plusPos = pattern.find('+');
    std::string startSequence = pattern.substr(0, plusPos); // '+' işaretinden önceki kısım
    std::string endSequence = pattern.substr(plusPos + 1);  // '+' işaretinden sonraki kısım

    std::vector<std::string> matches;

    // Metinde eşleşmeleri bulmak için bir döngü.
    size_t i = 0;
    while (i < text.size())
    {
        // Metin içinde başlangıç kısmıyla eşleşme olup olmadığını kontrol et.
        if (text.substr(i, startSequence.size()) == startSequence)
        {
            // '+' işaretine göre ardışık karakterleri kontrol et.
            size_t j = i + startSequence.size();
            while (j < text.size() && text[j] == startSequence.back())
            {
                j++;
            }
            // '+' işaretinden sonraki kısımla eşleşme olup olmadığını kontrol et.
            if (text.substr(j, endSequence.size()) == endSequence)
            {
                // Tam bir eşleşme bulunduğunda, bu kısmı ekle.
                matches.push_back(text.substr(i, j - i + endSequence.size()));
                // İndeksi güncelleyerek devam et.
                i = j + endSequence.size() - 1;
            }
            else
            {
                i++;
            }
        }
        else
        {
            i++;
        }
    }

    // Eşleşmeleri konsolda yazdır.
    for (const auto &match : matches)
    {
        std::cout << match << std::endl;
    }
}

void StarSign(const std::string &pattern, const std::string &text)
{
    // '*' sembolünün pozisyonunu bul
    size_t starPos = pattern.find('*');
    if (starPos == std::string::npos)
    {
        std::cerr << "Error: Pattern does not contain '*'" << std::endl;
        return;
    }

    // Başlangıç ve bitiş sekanslarını ayır
    std::string startSequence = pattern.substr(0, starPos);
    std::string endSequence = (starPos + 1 < pattern.size()) ? pattern.substr(starPos + 1) : "";

    if (startSequence.empty())
    {
        std::cerr << "Error: Start sequence is empty." << std::endl;
        return;
    }

    char beforeStar = startSequence.back(); // '*' işaretinden önceki karakter
    std::vector<std::string> matches;

    // Yıldız olmadan ilk eşleşmeyi oluştur
    std::string firstMatch = startSequence + endSequence;
    firstMatch.erase(std::remove(firstMatch.begin(), firstMatch.end(), beforeStar), firstMatch.end());
    matches.push_back(firstMatch);

    // Metin içinde sekansları kontrol et
    size_t i = 0;
    while (i < text.size())
    {
        if (i + startSequence.size() > text.size())
        {
            break; // StartSequence dışına çıkılmasın
        }

        // Başlangıç sekansını kontrol et
        if (text.substr(i, startSequence.size()) == startSequence)
        {
            size_t j = i + startSequence.size();

            // Yıldızdan önceki karakteri atla
            while (j < text.size() && text[j] == beforeStar)
            {
                j++;
            }

            // Bitiş sekansını kontrol et
            if (j + endSequence.size() <= text.size() &&
                text.substr(j, endSequence.size()) == endSequence)
            {
                matches.push_back(text.substr(i, j - i + endSequence.size()));
                i = j + endSequence.size(); // İndeksi ileri taşımak
            }
            else
            {
                i++;
            }
        }
        else
        {
            i++;
        }
    }

    // Eşleşmeleri konsola yazdır
    for (const auto &match : matches)
    {
        std::cout << match << std::endl;
    }
}

void CurlyBracket(const std::string &pattern, const std::string &text)
{
    std::vector<std::string> matches;

    // Metni boşluklara göre ayır.
    std::istringstream textStream(text);
    std::vector<std::string> textElements;
    std::string word;
    while (textStream >> word)
    {
        textElements.push_back(word);
    }

    // Start ve end sekanslarını belirle
    size_t openBracePos = pattern.find('{');
    size_t closeBracePos = pattern.find('}');

    if (openBracePos != std::string::npos && closeBracePos != std::string::npos)
    {
        std::string startSequence = pattern.substr(0, openBracePos);
        std::string repeatValues = pattern.substr(openBracePos + 1, closeBracePos - openBracePos - 1);

        std::vector<std::string> rangeValues;
        std::istringstream repeatStream(repeatValues);
        std::string token;
        while (std::getline(repeatStream, token, ','))
        {
            rangeValues.push_back(token);
        }

        if (rangeValues.size() == 2)
        {
            int start_value = std::stoi(rangeValues[0]);
            int max_repeat = rangeValues[1].empty() ? 20 : std::stoi(rangeValues[1]);

            for (int i = start_value; i <= max_repeat; i++)
            {
                // String'i elle tekrarla
                std::string new_pattern = "";
                for (int j = 0; j < i; j++)
                {
                    new_pattern += startSequence; // String'i j kadar tekrarla
                }

                if (std::find(textElements.begin(), textElements.end(), new_pattern) != textElements.end())
                {
                    matches.push_back(new_pattern);
                }
            }
        }
        else if (rangeValues.size() == 1)
        {
            int repeat = std::stoi(rangeValues[0]);

            // String'i elle tekrarla
            std::string new_pattern = "";
            for (int j = 0; j < repeat; j++)
            {
                new_pattern += startSequence; // String'i j kadar tekrarla
            }

            if (std::find(textElements.begin(), textElements.end(), new_pattern) != textElements.end())
            {
                matches.push_back(new_pattern);
            }
        }
    }

    // Eşleşmeleri konsola yazdır.
    for (const auto &match : matches)
    {
        std::cout << match << std::endl;
    }
}

void SquareBracket(const std::string &pattern, const std::string &text)
{
    // Kare parantez içindeki deseni çıkar
    size_t openBracket = pattern.find('[');
    size_t closeBracket = pattern.find(']');

    std::string insideBrackets = pattern.substr(openBracket + 1, closeBracket - openBracket - 1);
    std::string startPattern = pattern.substr(0, openBracket);
    std::string endPattern = pattern.substr(closeBracket + 1);

    // Metni kelimelere ayırın
    std::istringstream textStream(text);
    std::vector<std::string> splittedText;
    std::string word;
    while (textStream >> word)
    {
        splittedText.push_back(word);
    }

    // Eşleşmeleri kaydetmek için bir liste oluşturun
    std::vector<std::string> matches;

    // Metin içindeki kelimeleri kontrol edin
    for (const auto &word : splittedText)
    {
        // Başlangıç ve bitiş desenlerine uygun olup olmadığını kontrol edin
        if (word.find(startPattern) == 0 && word.rfind(endPattern) == (word.size() - endPattern.size()))
        {
            // Kare parantez içindeki desene uygun olup olmadığını kontrol edin
            if (word.find(insideBrackets) != std::string::npos)
            {
                matches.push_back(word);
            }
        }
    }

    // Eşleşmeleri yazdırın
    for (const auto &match : matches)
    {
        std::cout << match << std::endl;
    }
}

void Bracket(const std::string &pattern, const std::string &text)
{
    // Yuvarlak parantez içindeki ifadeleri toplamak için liste
    std::vector<std::string> matches;
    // Parantezler arasında olup olmadığını kontrol etmek için bayrak
    bool inParentheses = false;
    // Parantez içindeki karakterleri toplamak için geçici bir değişken
    std::string temp;

    // Metni kelimelere ayırın
    std::istringstream textStream(text);
    std::vector<std::string> splittedText;
    std::string word;
    while (textStream >> word)
    {
        splittedText.push_back(word);
    }

    // Deseni karakter bazında döngüyle tarayın
    for (const char &charac : pattern)
    {
        if (charac == '(')
        { // Parantez başlarsa
            inParentheses = true;
            temp.clear(); // Geçici değişkeni temizleyin
        }
        else if (charac == ')')
        { // Parantez kapanırsa
            if (inParentheses)
            {
                matches.push_back(temp); // Sonucu listeye ekleyin
                inParentheses = false;   // Bayrağı kapatın
            }
        }
        else if (inParentheses)
        { // Parantez içindeyken karakterleri toplayın
            temp += charac;
        }
    }

    // Elde edilen ifadeleri metin içinde kontrol edin ve eşleşmeleri yazdırın
    for (const auto &result : matches)
    {
        if (std::find(splittedText.begin(), splittedText.end(), result) != splittedText.end())
        {
            std::cout << result << std::endl;
        }
    }
}

void PowerSign(const std::string &pattern, const std::string &text)
{
    // 'text' kelimelerini ayırmak için boşlukla bölüyoruz
    std::istringstream textStream(text);
    std::vector<std::string> splittedText;
    std::string word;

    // Text'i kelimelere ayırıyoruz
    while (textStream >> word)
    {
        splittedText.push_back(word);
    }

    // 'pattern' içinde '^' karakterinden sonraki kısmı alıyoruz
    size_t caretPos = pattern.find('^');
    std::string startPattern;
    if (caretPos != std::string::npos)
    {
        startPattern = pattern.substr(caretPos + 1);
    }

    // Eşleşen kelimeleri tutmak için liste oluşturuyoruz
    std::vector<std::string> matches;

    // Tüm kelimeleri kontrol ediyoruz
    for (const auto &w : splittedText)
    {
        // Eğer kelime başlangıç paternine uyuyorsa, listeye ekliyoruz
        if (w.find(startPattern) == 0)
        {
            matches.push_back(w);
        }
    }

    // Eşleşen kelimeleri yazdırıyoruz
    for (const auto &match : matches)
    {
        std::cout << match << std::endl;
    }
}

void DollarSign(const std::string &pattern, const std::string &text)
{
    // 'text' içindeki kelimeleri boşlukla ayırın
    std::istringstream textStream(text);
    std::vector<std::string> splittedText;
    std::string word;

    // Text'i kelimelere ayırın
    while (textStream >> word)
    {
        splittedText.push_back(word);
    }

    // 'pattern' içinde '$' işaretinden önceki kısmı alın
    size_t dollarPos = pattern.find('$');
    std::string endPattern;
    if (dollarPos != std::string::npos)
    {
        endPattern = pattern.substr(0, dollarPos);
    }

    // Eşleşen kelimeleri tutmak için liste oluşturun
    std::vector<std::string> matches;

    // Her kelimeyi kontrol edin
    for (const auto &w : splittedText)
    {
        // Eğer kelime bitiş paternine uyuyorsa, listeye ekleyin
        if (w.size() >= endPattern.size() && w.compare(w.size() - endPattern.size(), endPattern.size(), endPattern) == 0)
        {
            matches.push_back(w);
        }
    }

    // Eşleşen kelimeleri yazdırın
    for (const auto &match : matches)
    {
        std::cout << match << std::endl;
    }
}

void PointSign(const std::string &pattern, const std::string &text)
{
    // 'text' içindeki kelimeleri boşluklarla ayırın
    std::istringstream textStream(text);
    std::vector<std::string> words;
    std::string word;

    // Text'i kelimelere ayırıyoruz
    while (textStream >> word)
    {
        words.push_back(word);
    }

    // 'pattern' içindeki '.' işaretine göre bölüyoruz
    size_t dotPos = pattern.find('.');
    std::string startPattern;
    std::string endPattern;

    if (dotPos != std::string::npos)
    {
        startPattern = pattern.substr(0, dotPos);
        endPattern = pattern.substr(dotPos + 1);
    }

    // Eşleşen kelimeleri tutmak için bir vektör oluşturuyoruz
    std::vector<std::string> matches;

    // Tüm kelimeleri kontrol ediyoruz
    for (const auto &w : words)
    {
        // Başlangıç ve bitiş desenlerine uyan ve uzunluğu aynı olan kelimeleri seçiyoruz
        if (w.size() == pattern.size() && w.find(startPattern) == 0 && w.rfind(endPattern) == w.size() - endPattern.size())
        {
            matches.push_back(w);
        }
    }

    // Eşleşen kelimeleri yazdırıyoruz
    for (const auto &match : matches)
    {
        std::cout << match << std::endl;
    }
}

void parser(const std::string &pattern, const std::string &text)
{
    std::vector<char> metacharacters = {'?', '|', '*', '+', '{', '[', '(', '^', '$', '.'};
    for (char c : pattern)
    {
        // Eğer karakter metakarakterler listesinde ise, uygun fonksiyonu çağırın
        if (std::find(metacharacters.begin(), metacharacters.end(), c) != metacharacters.end())
        {
            switch (c)
            {
            case '?':
                QuestionMark(pattern, text);
                break;
            case '|':
                OR(pattern, text);
                break;
            case '*':
                StarSign(pattern, text);
                break;
            case '+':
                PlusSign(pattern, text);
                break;
            case '{':
                CurlyBracket(pattern, text);
                break;
            case '[':
                SquareBracket(pattern, text);
                break;
            case '(':
                Bracket(pattern, text);
                break;
            case '^':
                PowerSign(pattern, text);
                break;
            case '$':
                DollarSign(pattern, text);
                break;
            case '.':
                PointSign(pattern, text);
                break;
            }
        }
    }
}

int main()
{
    std::string pattern, text;
    // Kullanıcıdan 'pattern' ve 'text' girdisini al
    std::cout << "Pattern giriniz: ";
    std::getline(std::cin, pattern); // Kullanıcıdan 'pattern' girdi alır
    std::cout << "Text giriniz: ";
    std::getline(std::cin, text); // Kullanıcıdan 'text' girdi alır

    // 'parser' fonksiyonunu çağır
    parser(pattern, text);

    return 0;
}