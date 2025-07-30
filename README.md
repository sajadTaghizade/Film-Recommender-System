<div dir="rtl">

<div align="center">
  <h1><b>🎬 پروژه "چی ببینم؟" (What to Watch?)</b></h1>
  <p>
    <b>یک سیستم پیشنهاددهنده فیلم هوشمند با دو رابط کاربری (خط فرمان و گرافیکی) که با C++ و SFML ساخته شده.</b>
  </p>
  
  <p>
    <a href="#-ویژگی‌های-کلیدی"><b>ویژگی‌ها</b></a> •
    <a href="#-تکنولوژی‌های-استفاده-شده"><b>تکنولوژی‌ها</b></a> •
    <a href="#-معماری-و-مفاهیم-حرفه‌ای"><b>مفاهیم حرفه‌ای</b></a> •
    <a href="#-چگونه-اجرا-کنیم"><b>راهنمای اجرا</b></a> •
  </p>
</div>

---

<h2 dir="rtl">🚀 درباره پروژه</h2>

<p dir="rtl">
سلام پروژه ای که طراحی کردم سعی کردم از تمام اصولی که در درس ap یاد گرفتیم استفاده کنم
</p>
<p dir="rtl">
من یک سیستم پیشنهاددهنده فیلم ساختم که بر اساس سابقه کاربر یا به صورت عمومی، فیلم پیشنهاد می‌ده. اما بخش جذاب پروژه در <b>چگونگی</b> پیاده‌سازی اونه. من از تمام امکانات  C++ مدرن، اصول طراحی نرم‌افزار (مثل <b>SOLID</b>)، الگوهای طراحی (مثل <b>Strategy</b>) و در نهایت کتابخانه  <b>SFML</b> برای ساخت یک رابط کاربری گرافیکی زیبا استفاده کردم.
</p>
<p dir="rtl">
این پروژه دو تا خروجی داره:
<ol>
  <li>یک نسخه <b>خط فرمان (CLI)</b> برای اجرای سریع و تست منطق برنامه.</li>
  <li>یک نسخه <b>گرافیکی (GUI)</b> با ظاهر مدرن، عکس‌ها و انیمیشن‌های نرم برای یک رابط کاربری .</li>
</ol>
</p>
<br>

---

<h2 dir="rtl">✨ ویژگی‌های کلیدی</h2>

<table align="center" width="100%">
  <tr style="background-color: transparent;">
    <td align="center" width="33%">
      <sub dir="rtl"><b>رابط کاربری دوگانه (CLI & GUI)</b></sub><br>
      <p dir="rtl"><small>هم با دستورات متنی در ترمینال کار می‌کنه و هم با یک رابط گرافیکی جذاب که با SFML ساخته شده.</small></p>
    </td>
    <td align="center" width="33%">
      <sub dir="rtl"><b>سیستم پیشنهاد هوشمند</b></sub><br>
      <p dir="rtl"><small>برای کاربران با سابقه، بر اساس سلیقه شخصی و برای کاربران جدید، بر اساس آمار کلی فیلم پیشنهاد می‌ده.</small></p>
    </td>
    <td align="center" width="33%">
      <sub dir="rtl"><b>کدنویسی اصولی</b></sub><br>
      <p dir="rtl"><small>استفاده کامل از مفاهیم شیءگرایی پیشرفته، اصول  الگوهای طراحی و ویژگی‌های C++17.</small></p>
    </td>
  </tr>
</table>

<br>

---

<h2 dir="rtl">🛠 تکنولوژی‌های استفاده شده</h2>
<p dir="rtl">
در این پروژه از ابزارها و کتابخانه‌های مدرن و استاندارد استفاده شده:
</p>
<p align="center">
  <a href="https://isocpp.org/"><img src="https://img.shields.io/badge/C++-17-blue.svg?style=for-the-badge&logo=c%2B%2B" alt="C++17"></a>
  &nbsp;
  <a href="https://www.sfml-dev.org/"><img src="https://img.shields.io/badge/SFML-2.6-green.svg?style=for-the-badge&logo=sfml" alt="SFML"></a>
  &nbsp;
  <a href="https://www.gnu.org/software/make/"><img src="https://img.shields.io/badge/Makefile-GNU-blueviolet.svg?style=for-the-badge&logo=gnu-make" alt="Makefile"></a>
</p>

---

<h2 dir="rtl">🏛️ مفاهیم حرفه‌ای</h2>
<p dir="rtl">
در بخش میخوام از تمام بخش هایی که برای حرفه ای تر شدن پروژه استفاده کردم توضیح بدم
</p>

<h3 dir="rtl">۱. شیءگرایی پیشرفته (Advanced OOP) 🏛️</h3>
<ul dir="rtl">
  <li><b>کپسوله‌سازی (Encapsulation):</b> هر کلاس، داده‌ها و رفتارهای مربوط به خودش را در بر می‌گیرد. برای مثال، کلاس <code>Film</code> و <code>User</code> اطلاعات مربوط به خود را مدیریت می‌کنند.</li>
  <li><b>انتزاع (Abstraction):</b>  پیچیدگی‌ها را پشت یک رابط کاربری ساده پنهان شده. کلاس <code>Recommender</code> مثل یک "موتور" عمل می‌کند و رابط گرافیکی فقط از متدهای ساده آن استفاده می‌کند، بدون اینکه از منطق داخلی خبر داشته باشد.</li>
  <li><b>ارث‌بری و چندریختی (Inheritance & Polymorphism):</b>  یک اینترفیس به نام <code>IScoringStrategy</code> تعریف شده و کلاس‌های <code>HistoryScorer</code> و <code>GenericScorer</code> از آن ارث‌بری کردند. این کار به  اجازه میدهد که با هر دو الگوریتم امتیازدهی مثل یک چیز واحد رفتار شود.</li>
</ul>

<h3 dir="rtl">۲. اصول طراحی SOLID 🧱</h3>
<p dir="rtl">
این ۴ اصل، برای رعایت این اصول اجرا شده:
</p>
<ul dir="rtl">
  <li><b>Single Responsibility:</b> هر کلاس فقط یک مسئولیت داشت. <code>Recommender</code> مسئول مدیریت منطق، <code>Scorer</code>ها مسئول امتیازدهی، و...  </li>
  <li><b>Open/Closed:</b> معماری  برای <b>توسعه</b> باز بود اما برای <b>تغییر</b> بسته بود. اگر می‌خواستم یک الگوریتم جدید اضافه کنم، کافی بود یک کلاس جدید از <code>IScoringStrategy</code> بسازم، بدون اینکه نیازی به تغییر کد <code>Recommender</code> باشد.</li>
  <li><b>Dependency Inversion:</b> کلاس سطح بالای <code>Recommender</code> به کلاس‌های سطح پایین <code>HistoryScorer</code> یا <code>GenericScorer</code> وابسته نبود، بلکه هر دو به یک <b>انتزاع</b> به نام <code>IScoringStrategy</code> وابسته بودند.</li>
</ul>

<h3 dir="rtl">۳.  C++  (C++17) ✨</h3>
<ul dir="rtl">
  <li><b>اشاره‌گرهای هوشمند (<code>std::unique_ptr</code>):</b> برای مدیریت اشیاء <code>Scorer</code> و  از اشاره‌گرهای هوشمند استفاده شد تا مدیریت حافظه به صورت خودکار و امن انجام شود و نگرانی ای برای نشت حافظه (Memory Leak) نباشد.</li>
  <li><b>کتابخانه استاندارد قالب (STL):</b> از تمام قدرت کانتینرهای STL مثل <code>std::vector</code>، <code>std::map</code> و <code>std::set</code> برای مدیریت بهینه داده‌ها استفاده شد.</li>
  <li><b>عبارات لامبدا (Lambda Expressions):</b> برای تعریف منطق‌های پیچیده مرتب‌سازی و همچنین برای تعریف عملکرد دکمه‌ها (<code>set_on_click</code>)، از لامبداها استفاده شد که کد را بسیار تمیز و .ژولار می‌کند.</li>
</ul>

<h3 dir="rtl">۴.  الگوهای حرفه‌ای تر🛠️</h3>
<ul dir="rtl">
  <li><b>الگوی استراتژی (Strategy Pattern):</b> با جدا کردن کامل الگوریتم‌های امتیازدهی از بدنه اصلی برنامه، امکان طراحی کدی بسیار انعطاف‌پذیر و قابل توسعه فراهم شد.</li>
  <li><b>ماشین حالت (State Machine):</b> در نسخه گرافیکی، از یک <code>enum class AppState</code> برای مدیریت صفحات مختلف (لاگین، منو، نتایج و...) استفاده شد تا از نوشتن کدهای پیچیده و تو در تو جلوگیری شود.</li>
  <li><b>سیستم ساخت پیشرفته (<code>Makefile</code>):</b> من یک <code>Makefile</code> حرفه‌ای طراحی کردم که قادر به ساخت <b>دو فایل اجرایی کاملاً مجزا</b> (<code>ChiBebinam</code> و <code>ChiBebinam_sfml</code>) از یک سورس کد مشترک است و کدهای گرافیکی را فقط برای نسخه گرافیکی کامپایل می‌کند.</li>
</ul>

### ۵. استفاده  از تمپلیت‌ها 
<p dir="rtl">
برای جلوگیری از تکرار کد و نوشتن کدی که واقعاً قابل استفاده مجدد باشد، از قدرت تمپلیت‌های C++ استفاده کردم
ترین مثال برای این موضوع، کلاس جنریک <code>DataLoader</code> است
</p>


<p dir="rtl">
<b>مشکل چه بود؟</b>
</p>
<p dir="rtl">
 دو تابع جداگانه برای خواندن اطلاعات از فایل‌های CSV بودیکی برای فیلم‌ها (<code>read_films</code>) و دیگری برای کاربران (<code>read_users</code>). منطق داخلی این دو تابع تقریباً ۹۰٪ یکسان بود که این موضوع اصل مهم <b> (Don't Repeat Yourself)</b> را نقض می‌کرد.
</p>

<p dir="rtl">
<b>راه‌حل با تمپلیت:</b>
</p>
<p dir="rtl">
 یک کلاس تمپلیت به نام <code>DataLoader&lt;T&gt;</code> ساختممی‌تواند هر نوع داده‌ای را از یک فایل CSV بخواند.
</p>



---

<h2 dir="rtl">⚙️ چگونه اجرا بکنید؟</h2>
<p dir="rtl">
کتاب خونه رو باید نصب کنی</p>
<details dir="rtl">
  <summary><b>نصب SFML در اوبونتو/</b></summary>
  <br>
  <p dir="rtl"> دستور زیر را در ترمینال وارد کنید:</p>
  <pre><code>sudo apt-get install libsfml-dev</code></pre>
</details>

<br>

<p dir="rtl">
بعد از نصب، مراحل زیر رو دنبال کنید:
</p>

<ol dir="rtl">
  <li>
   
  <li>
    <b>کامپایل کردن:</b>
    <p dir="rtl">فقط کافیه دستور <code>make</code> رو در ریشه پروژه اجرا کنی. این دستور هر دو نسخه خط فرمان و گرافیکی رو برات می‌سازه.</p>
    <pre><code>make</code></pre>
  </li>
  <li>
    <b>اجرای برنامه:</b>
    <ul dir="rtl">
      <li><b>نسخه خط فرمان:</b></li>
      <pre><code>./ChiBebinam path/to/users/file.csv path/to/films/file.csv</code></pre>
      <li><b>نسخه گرافیکی (پیشنهادی!):</b></li>
      <pre><code>./ChiBebinam_sfml path/to/users/file.csv path/to/films/file.csv</code></pre>
    </ul>
  </li>
</ol>
<br>
<br>

<div dir="rtl">
<table align="center" width="90%">
  <tr style="background-color: #44475a;">
    <td align="center" width="80" style="border: none;">
    </td>
    <td style="border: none;">
      <h2 style="color: #ffb86c; margin-bottom: 0px;">نکته بسیار مهم</h2>
      <p style="color: #f8f8f2; margin-top: 5px;">
        نسخه گرافیکی برنامه (<code>ChiBebinam_sfml</code>) صرفاً با داده‌های اصلی ارائه شده همراه پروژه (فایل‌های <code>films.csv</code> و <code>users.csv</code>) به درستی کار می‌کند. دلیل این موضوع این است که فایل‌های عکس بازیگران، ژانرها و پوسترها به صورت دستی و هماهنگ با نام‌های موجود در این فایل‌ها ساخته شده‌اند.
        <br><br>
        اگر از فایل‌های داده دیگری استفاده کنید، برنامه همچنان اجرا می‌شود اما قادر به یافتن و نمایش عکس‌ها نخواهد بود.
      </p>
    </td>
  </tr>
</table>
</div>
<br>