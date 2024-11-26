// header.html 내용
const headerHTML = `
    <header>
        <h1>Flavor Cloud</h1>
        <nav>
            <ul>
                <li><a href="index.html">홈</a></li>
                <li><a href="category1.html">액상</a></li>
                <li><a href="category2.html">브랜드</a></li>
                <li><a href="about.html">회사 소개</a></li>
                <li><a href="contact.html">연락처</a></li>
            </ul>
        </nav>
    </header>
`;

// footer.html 내용
const footerHTML = `
    <footer>
        <p>&copy; 2024 전자담배 액상 쇼핑몰. 모든 권리 보유.</p>
    </footer>
`;

// 헤더와 푸터 삽입
document.getElementById('header').innerHTML = headerHTML;
document.getElementById('footer').innerHTML = footerHTML;
