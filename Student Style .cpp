#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

struct Product {
    std::string name;
    std::string category;
    double price;
    std::string amazonLink;

    Product(const std::string& n, const std::string& c, double p, const std::string& link)
        : name(n), category(c), price(p), amazonLink(link) {}
};

struct StudentData {
    std::string studentName;
    std::string productName;
    std::string gender;  // New field for gender
    int age;             // New field for age

    StudentData(const std::string& s, const std::string& p, const std::string& g, int a)
        : studentName(s), productName(p), gender(g), age(a) {}
};

class ProductRecommender {
public:
    ProductRecommender() {}

    void addProduct(const Product& product) {
        productCatalog.push_back(product);
        updateCategoryTrends(product.category);
    }

    void addStudentData(const StudentData& data) {
        studentData.push_back(data);
    }

    std::vector<Product> recommendProducts(const std::string& gender, int age) {
        std::vector<Product> recommendedProducts;

        std::unordered_map<std::string, int> productCount;
        for (const StudentData& student : studentData) {
            if (student.gender == gender && student.age == age) {
                productCount[student.productName]++;
            }
        }

        std::priority_queue<std::pair<int, std::string>> productQueue;
        for (const auto& entry : productCount) {
            productQueue.push({entry.second, entry.first});
        }

        int recommendationsCount = std::min(5, static_cast<int>(productQueue.size()));
        for (int i = 0; i < recommendationsCount; ++i) {
            std::string productName = productQueue.top().second;
            productQueue.pop();

            for (const Product& product : productCatalog) {
                if (product.name == productName) {
                    recommendedProducts.push_back(product);
                    break;
                }
            }
        }

        return recommendedProducts;
    }

private:
    std::vector<Product> productCatalog;
    std::vector<StudentData> studentData;
    std::unordered_map<std::string, int> categoryTrends;

    void updateCategoryTrends(const std::string& category) {
        if (categoryTrends.find(category) != categoryTrends.end()) {
            categoryTrends[category]++;
        } else {
            categoryTrends[category] = 1;
        }
    }
};

int main() {
    ProductRecommender recommender;

    recommender.addProduct({"Laptop", "Electronics", 999.99, "https://www.amazon.in/s?k=Laptop"});
    recommender.addProduct({"T-shirt", "Clothing", 19.99, "https://www.amazon.in/s?k=T-shirt"});
    recommender.addProduct({"Book", "Books", 12.99, "https://www.amazon.in/s?k=Book"});

    recommender.addStudentData({"Student1", "Laptop", "Male", 25});
    recommender.addStudentData({"Student2", "T-shirt", "Female", 22});

    std::string userGender;
    int userAge;

    std::cout << "Enter your gender (Male/Female): \n";
    std::cin >> userGender;

    std::cout << "Enter your age: ";
    std::cin >> userAge;

    std::vector<Product> recommendations = recommender.recommendProducts(userGender, userAge);

    std::cout << "\nTop 5 Recommended Products on Amazon India based on Trends for your Gender and Age:\n";
    for (const Product& product : recommendations) {
        std::cout << "Name: " << product.name << "\n";
        std::cout << "Category: " << product.category << "\n";
        std::cout << "Price: Rupees" << product.price << "\n";
        std::cout << "Amazon India Link: " << product.amazonLink << "\n\n";
    }

    return 0;
}

