# Mid-term Exam - Data Structures and Algorithms (DSA)
MSSV: 3123411257
Họ và tên: Võ Minh Sang
lớp: DCT123C5, Đại Học Sàì Gòn

# Hệ Thống Quản Lý Hội Đồng (v1.0)
## Mô tả chung

Chương trình này được thiết kế để quản lý hội đồng của các khoa trong một trường đại học. Mỗi hội đồng bao gồm 3 giảng viên từ cùng một khoa. Chương trình cho phép người dùng nhập thông tin về thời gian rảnh của giảng viên, sau đó tự động tạo hội đồng dựa trên thông tin này. Với các chức năng cơ bản như:
- Kiểm tra hai hội đồng khác khoa có trùng thời gian diễn ra không?
- Kiểm tra các hội đồng mà một Giảng Viên đang tham gia trong tuần
- In ra thời gian biểu các hội đồng sắp diễn ra trong tuần

## Cấu trúc dữ liệu

Chương trình sử dụng các cấu trúc dữ liệu sau:

- `KhoangThoiGianRanh`: Lưu trữ một khoảng thời gian rảnh, bao gồm thứ trong tuần và giờ bắt đầu và kết thúc.
- `chuyenDoiTime`: Lưu trữ danh sách các khoảng thời gian rảnh cho mỗi ngày trong tuần.
- `nodeGiangVien`: Lưu trữ thông tin về một giảng viên, bao gồm tên, học hàm/học vị, thời gian rảnh và con trỏ đến giảng viên tiếp theo trong danh sách (cấu trúc danh sách liên kết).
- `nodeHoiDong`: Lưu trữ thông tin về một hội đồng, bao gồm tên khoa, thời gian tổ chức, danh sách thành viên và con trỏ đến hội đồng tiếp theo trong danh sách.
- `Khoa`: Lưu trữ thông tin về một khoa, bao gồm con trỏ đến đầu danh sách giảng viên, số lượng giảng viên và con trỏ đến đầu danh sách hội đồng.

## Các hàm chính

Chương trình sử dụng các hàm chính sau:

- `themThanhVienVaoKhoa`: Thêm một giảng viên vào danh sách giảng viên của một khoa.
- `timGiaoThoiGianRanh`: Tìm giao của thời gian rảnh của 3 giảng viên đưa vào. ý tưởng: Nếu thời gian kết thúc của một giảng viên lớn hơn thời gian bắt đầu của giảng viên khác (và ngược lại), thì chương trình sẽ xác định rằng có thời gian rảnh chung. 
- `kiemTraTrungLich`: Kiểm tra xem hai hội đồng khác khoa có trùng lịch tổ chức hay không.
- `taoHoiDong`: Tạo một hội đồng từ 3 giảng viên và thêm hội đồng này vào danh sách hội đồng của một khoa.
- `timKiemHoiDongTheoGiangVien`: Tìm kiếm hội đồng theo tên giảng viên.
- `hienThiThoiGianBieu`: Hiển thị thời gian biểu của tất cả các hội đồng.

## Cách sử dụng

Khi chạy chương trình, người dùng sẽ được yêu cầu nhập thông tin về thời gian rảnh của giảng viên. Sau đó, chương trình sẽ tự động tạo hội đồng dựa trên thông tin này.

Người dùng cũng có thể chọn kiểm tra xem hai hội đồng bất kỳ có trùng lịch tổ chức hay không, tìm kiếm hội đồng theo khoa và tên giảng viên, hoặc hiển thị thời gian biểu của tất cả các hội đồng.

## Trường hợp đặc biệt đã xử lý

1. Trùng lịch: Chương trình đã xử lý trường hợp hai hội đồng có thể tổ chức cùng một thời điểm. Trước khi thêm một hội đồng mới vào danh sách, chương trình sẽ kiểm tra xem thời gian tổ chức của hội đồng mới có trùng với thời gian tổ chức của bất kỳ hội đồng nào khác trong cùng một khoa hay không. Nếu có, hội đồng mới sẽ không được thêm vào danh sách.

2. Thời gian rảnh: Chương trình yêu cầu người dùng nhập thời gian rảnh của mỗi giảng viên. Nếu người dùng nhập một khoảng thời gian không hợp lệ (ví dụ, giờ bắt đầu lớn hơn giờ kết thúc, ngoài giờ làm việc ...), chương trình sẽ yêu cầu người dùng nhập lại.

3. Tìm kiếm hội đồng: Khi tìm kiếm hội đồng theo tên giảng viên, nếu không tìm thấy giảng viên trong danh sách, chương trình sẽ thông báo rằng không tìm thấy giảng viên.

4. Và nhiều trường hợp nhập dữ liệu vô nghĩa khác sẽ đều có thông báo lỗi và yêu cầu nhập lại 

## Quy ước trong code

0. Các hội đùng cùng một khoa không được diễn ra cùng lúc.
   
2. Thứ trong tuần: Thứ 2 được biểu diễn bằng số 2, thứ 3 bằng số 3, v.v., và thứ 7 bằng số 7. Thứ 2 có chỉ số 0 trong danh sách thời gian rảnh, thứ 3 có chỉ số 1, v.v.

3. Giờ trong ngày: Giờ trong ngày được biểu diễn bằng số nguyên từ 0 đến 23, với 0 tượng trưng cho 12 giờ đêm và 23 tượng trưng cho 11 giờ tối.

4. Khoa: Khoa được biểu diễn bằng số nguyên từ 1 đến 7, với 1 tượng trưng cho "Khoa Công nghệ thông tin", 2 tượng trưng cho "Khoa Luật", v.v., và 7 tượng trưng cho "Khoa Thư viện – Văn phòng".

5. Giảng viên: Mỗi giảng viên trong một khoa được biểu diễn bằng một số nguyên, với số nguyên đầu tiên tượng trưng cho giảng viên đầu tiên được thêm vào danh sách của khoa.

## TEST CASE

1. Không có thời gian rảnh của các giảng viên giao nhau để tạo hội đồng:

   - Chọn khoa: 1 (Khoa Công nghệ Thông tin)
   - Số lượng người đã biết thời gian rảnh: 3
   - Chọn giảng viên: 1
     - Thứ 2: nhập thời gian từ 8h đến 10h
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 2
     - Thứ 2: nhập thời gian từ 12h đến 13h
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 3
     - Thứ 2: nhập thời gian từ 14h đến 16h
     - Bỏ qua các thứ còn lại (-2)
   - chọn không nhập tiếp: 2
   - chọn hiển thị thời gian biểu: 3
   - Kết quả: Chương trình sẽ thông báo không thể tạo hội đồng vì không có thời gian rảnh chung giữa các giảng viên và kết thúc chương trình.

2. Có thời gian rảnh của các giảng viên giao nhau để tạo hội đồng:
   - Chọn khoa: 1 (Khoa Công nghệ Thông tin)
   - Nhập số người đã biết 3
   - Chọn giảng viên: 1
     - Thứ 2: nhập thời gian từ 8h đến 10h
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 2
     - Thứ 2: nhập thời gian từ 9h đến 11h
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 3
     - Thứ 2: nhập thời gian từ 9h đến 10
     - Bỏ qua các thứ còn lại (-2)
   - Chọn không nhập tiếp: 2
   - Chọn hiển thị thời gian biểu: 3
   - Kết quả: Chương trình sẽ tạo hội đồng với thời gian từ 9h đến 9h30 vào thứ 2.

3. Kiểm tra hai hội đồng khác khoa có trùng lịch diễn ra hay không
   - Chọn khoa: 1 (Khoa Công nghệ Thông tin)
   - Nhập số người đã biết 3
   - Chọn giảng viên: 1
     - Thứ 2: nhập thời gian từ 8h đến 10h
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 2
     - Thứ 2: nhập thời gian từ 9h đến 11h
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 3
     - Thứ 2: nhập thời gian từ 9h đến 10
     - Bỏ qua các thứ còn lại (-2)
   - chọn nhập tiếp: 1
   - chọn khoa: 2 (luật)
   - Nhập số người đã biết 3
   - Chọn giảng viên: 1
   - Thứ 2: nhập thời gian từ 8h đến 10h
   - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 2
     - Thứ 2: nhập thời gian từ 9h đến 11h
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 3
     - Thứ 2: nhập thời gian từ 9h đến 10
     - Bỏ qua các thứ còn lại (-2)
   - Chọn không nhập tiếp: 2
   - chọn kiểm tra hai hội đồng có trùng lịch không:
   - hội đồng 1: 1
   - hội đồng 2: 2
     kết quả: hai hội đồng có trùng lịch

4. Tìm kiếm Giảng Viên đang tham gia hội đồng nào
   - Chọn khoa: 1 (Khoa Công nghệ Thông tin)
   - Nhập số người đã biết 3
   - Chọn giảng viên: 1
     - Thứ 2: nhập thời gian từ 8h đến 10h
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 2
     - Thứ 2: nhập thời gian từ 9h đến 11h
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 3
     - Thứ 2: nhập thời gian từ 9h đến 10
     - Bỏ qua các thứ còn lại (-2)
   - Chọn không nhập tiếp: 2
   - Chọn Tiềm hội đồng Giảng Viên đang tham gia: 2
   - Điền khoa của Giảng Viên: 1
   - Điền thứ tự của Giảng Viên: 2
     Kết quả: trả về thành viên trong hội đồng đang quản tham gia, thứ 2 lúc 9h đến 9h30

5. Hai hội đồng cùng một khoa không trùng thời gian nhau
   - Chọn khoa: 1 (Khoa Công nghệ Thông tin)
   - Nhập số người đã biết 6
   - Chọn giảng viên: 1
     - Thứ 2: nhập thời gian từ 8h đến 10h
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 2
     - Thứ 2: nhập thời gian từ 9h đến 11h
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 3
     - Thứ 2: nhập thời gian từ 9h đến 10
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 4
     - Thứ 2: nhập thời gian từ 9h đến 10
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 4
     - Thứ 2: nhập thời gian từ 14h đến 17
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 6
     - Thứ 2: nhập thời gian từ 10h đến 17
     - Bỏ qua các thứ còn lại (-2)
   - Chọn không nhập tiếp: 2
   - Chọn xem thời gian biểu: 3
      kết quả: hai hội đồng với các thành viên khác nhau diễn ra lần lượt 9-9.5 và 14-14.5

## Tính năng cần cải thiện trong tương lai
   - Thông báo và kết thúc ngay sau khi nhập thời gian nhưng không có thời gian rảnh chung của những người đó (thay vì kết thúc khi phải chọn option hiện thời gian biểu, nó không sai)
   - nếu hai khoa khác nhau trùng lịch thì cho người dùng chọn option có muốn xóa hội đồng này không
   - nhập vào thứ và khoảng giờ để xem tất cả các hội đồng có trong thứ, khoảng đó thôi thây vì chỉ có thể in ra toàn bộ hội đồng cả tuần, thực tế sẽ rất nhiều
   - Thêm tính năng đọc thời gian rảnh từ file, vì có thể GV báo với trường một thời thời gian rảnh cố định trong tuần thì tránh nhập đi nhập lại của người này vào lúc đó
   - 
## Các bug cần fix trong tương lai để hoàn thiện hơn (liệu có nên nói? với em, không chỉ vì một hai con số trên tờ a4 nên những dòng sau đây là lời thú nhận)
- Mỗi hội đồng diễn ra trong 30 phút, dữ liệu cho ra thời gian rảnh của cả 3 đủ để tạo nhiều hơn 1 hội đồng, em chưa thể lưu hoạc tạo để tối ưu toàn bộ thời gian rảnh của thầy cô (thôi thì để thầy cô nghỉ ngơi đi, một ngày một hội đồng là được rồi hen "đây không phải bug-đây là tính năng")
- Khi nhập lại một ngày hai lần em vẫn chưa kiểm sóat nó sẽ lưu vào đâu, đè hay thêm mới trong ngày này luôn ?? (thôi thì để đơn giản thì một ngày rảnh một khoảng thoi he)
- ...
