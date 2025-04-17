#include "Article.h"

Article::Article(const std::vector<std::string>& auth, const std::string& pubName,
    const std::string& artTitle, int yr)
    : authors(auth), publicationName(pubName), articleTitle(artTitle), year(yr) {}

Article::Article(const Article& other)
    : authors(other.authors), publicationName(other.publicationName),
    articleTitle(other.articleTitle), year(other.year) {}

Article::Article(Article&& other) noexcept
    : authors(std::move(other.authors)),
    publicationName(std::move(other.publicationName)),
    articleTitle(std::move(other.articleTitle)),
    year(other.year) {}

Article::~Article() {}

// Copy assignment operator
Article& Article::operator=(const Article& other) {
    if (this != &other) {
        authors = other.authors;
        publicationName = other.publicationName;
        articleTitle = other.articleTitle;
        year = other.year;
    }
    return *this;
}

// Move assignment operator
Article& Article::operator=(Article&& other) noexcept {
    if (this != &other) {
        authors = std::move(other.authors);
        publicationName = std::move(other.publicationName);
        articleTitle = std::move(other.articleTitle);
        year = other.year;
    }
    return *this;
}

const std::vector<std::string>& Article::getAuthors() const {
    return authors;
}

std::string Article::getPublicationName() const {
    return publicationName;
}

std::string Article::getArticleTitle() const {
    return articleTitle;
}

int Article::getYear() const {
    return year;
}

void Article::setAuthors(const std::vector<std::string>& auth) {
    authors = auth;
}

void Article::setPublicationName(const std::string& pubName) {
    publicationName = pubName;
}

void Article::setArticleTitle(const std::string& artTitle) {
    articleTitle = artTitle;
}

void Article::setYear(int yr) {
    year = yr;
}

