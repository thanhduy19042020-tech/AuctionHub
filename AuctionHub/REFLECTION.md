1. Lý do sử dụng từng thuật toán
- Insertion Sort(Live Auction Monitor): Do độ phức tạp đạt O(n) đối với dữ liệu gần như được sắp xếp sẵn. Vì vậy, thuật toán này phù hợp với những đầu vào có độ chênh lệch không nhiều (Task A)
- Selection Sort(Top-K Bid Finder): Hữu ích khi cần lấy nhanh một vài phần tử đứng đầu trên tập dữ liệu nhỏ. Cách này hạn chế những thao tác hoán đổi không cần thiết so với việc sắp xếp toàn bộ dữ liệu khi chỉ cần lấy Top 3 (Task B)
- Interchange Sort(Price Anomaly Validator): Logic đơn giản, dễ cài đặt bộ đếm thao tác swap. Thuật toán phù hợp để kiểm thử các lô dữ liệu nhỏ (Task C)
- Bubble Sort Early Stop (Stabilization Detector): Chương trình có thể dừng ngay lần duyệt đầu tiên nếu không có swap nào được thực hiện. Điều này giúp chương trình nhanh chóng nhận biết dữ liệu đã được sắp xếp và tránh thực hiện những lượt duyệt không cần thiết.(Task D)
- Quick Sort (Full Historical Sorter): Do có độ phức tạp trung bình là O(n log n), thích hợp để sắp xếp 1 nguồn dữ liệu lớn. Việc sử dụng phương pháp chọn chốt Median-of-three giúp giảm khả năng lựa chọn pivot không phù hợp(Task E)
2. Runtime của Quick Sort trên 100k records:
- Thời gian đo được là: 139 ms
- Kết quả cho thấy Quick Sort có khả năng xử lý tương đối hiệu quả một tập dữ liệu lớn
3. Bug gặp phải và cách khắc phục:
- Lỗi: Không thể chạy được file do trình biên dịch không tìm thấy địa chỉ của file
- Cách khắc phục: sử dụng LLM (ChatGPT) để tìm hiểu về lỗi, sử dụng các đường dẫn mà LLM hướng dẫn để đưa Terminal về đúng đường dẫn của file
4. Các Prompt đã dùng với LLM:
- [Green] "Hãy cho tôi bộ dữ liệu đầu vào để kiểm thử"
- [Green] "Giải thích hàm quickSortWrapper"
- [Yellow] "File báo lỗi: 'C:\Users\Dell\OneDrive\Desktop\DSA\auctionhub.exe' is not recognized as the name of a 
cmdlet, function, script file, or operable program. Check the spelling of the name, or if a path was included, verify that the path is correct and try again. At line:1 char:3 & C:\Users\Dell\OneDrive\Desktop\DSA\auctionhub.exe...', hướng dẫn cách sửa"
    
5.Độ phức tạp trường hợp xấu nhất của Quick Sort(Median-of-three):
- Độ phức tạp của quick sort có thể đạt O(n^2) vì đối với một số dạng dữ liệu đặc biệt, chẳng hạn tập dữ liệu chứa nhiều phần tử có giá trị bằng nhau khi sử dụng phương pháp phân hoạch không phù hợp, thuật toán có thể liên tục tạo ra các phần mảng mất cân bằng. Khi đó, một phần có thể chứa gần như toàn bộ phần tử, trong khi phần còn lại chỉ chứa rất ít hoặc không có phần tử nào.

