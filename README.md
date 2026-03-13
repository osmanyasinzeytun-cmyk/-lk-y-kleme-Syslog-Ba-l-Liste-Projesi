# Linux Syslog Yönetimi - Çift Yönlü Bağlı Liste (Doubly Linked List) Uygulaması

Bu proje, Linux işletim sistemindeki sistem günlüklerini (syslog) analiz etmek ve bu verileri dinamik bir veri yapısı olan **Çift Yönlü Bağlı Liste** kullanarak bellekte yönetmek amacıyla geliştirilmiştir.

## 📋 Proje Özeti
Bu çalışma kapsamında, Linux sistem günlüklerinin yapısı incelenmiş ve bu verilerin kronolojik olarak saklanması, ileri ve geri yönlü listelenmesi için optimize edilmiş bir uygulama tasarlanmıştır.

## ⚙️ Teknik Detaylar
- **Veri Yapısı:** Çift Yönlü Bağlı Liste (Doubly Linked List)
- **Programlama Dili:** C
- **Bellek Yönetimi:** Dinamik bellek tahsisi (`malloc`) ve güvenli bellek temizliği (`free`)

## 🛠️ Neden Çift Yönlü Bağlı Liste?
Projede veri yapısı seçimi yapılırken şu teknik kriterler göz önünde bulundurulmuştur:
1. **Hızlı Veri Ekleme:** Syslog verileri sürekli akan bir yapıdadır. Çift yönlü bağlı listede `tail` (kuyruk) işaretçisi kullanılarak yeni kayıtlar listenin sonuna $O(1)$ karmaşıklığı ile eklenir.
2. **Çift Yönlü Analiz:** Sistem yönetiminde hata analizi yapılırken genellikle en son gerçekleşen olaylar kritiktir. Çift yönlü yapı, `prev` (önceki) işaretçileri sayesinde listenin sonundan başına doğru (ters kronolojik) tarama yapılmasına imkan tanır.
3. **Esneklik:** Sabit boyutlu dizilerin aksine, log sayısı arttıkça bellek kullanımı dinamik olarak genişleyebilir.

## 🚀 Çalıştırma Talimatları
Uygulamayı yerel makinenizde çalıştırmak için:

1. Depoyu klonlayın veya dosyaları indirin.
2. Kodun bulunduğu dizinde bir `syslog.txt` dosyası olduğundan emin olun.
3. Terminal üzerinden aşağıdaki komutları çalıştırın:

```bash
gcc syslog_linkedlist.c -o syslog_app
./syslog_app

