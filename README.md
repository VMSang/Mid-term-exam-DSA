# Mid-term Exam - Data Structures and Algorithms (DSA)
MSSV: 3123411257
Họ và tên: Võ Minh Sang
lớp: DCT123C5, Đại Học Sàì Gòn

# Hệ Thống Quản Lý Hội Đồng
## Mô tả chung

Chương trình này được thiết kế để quản lý hội đồng của các khoa trong một trường đại học. Mỗi hội đồng bao gồm 3 giảng viên từ cùng một khoa. Chương trình cho phép người dùng nhập thông tin về thời gian rảnh của giảng viên, sau đó tự động tạo hội đồng dựa trên thông tin này.

## Cấu trúc dữ liệu

Chương trình sử dụng các cấu trúc dữ liệu sau:

- `KhoangThoiGianRanh`: Lưu trữ một khoảng thời gian rảnh, bao gồm thứ trong tuần và giờ bắt đầu và kết thúc.
- `chuyenDoiTime`: Lưu trữ danh sách các khoảng thời gian rảnh cho mỗi ngày trong tuần.
- `nodeGiangVien`: Lưu trữ thông tin về một giảng viên, bao gồm tên, học hàm/học vị, thời gian rảnh và con trỏ đến giảng viên tiếp theo trong danh sách.
- `nodeHoiDong`: Lưu trữ thông tin về một hội đồng, bao gồm tên khoa, thời gian tổ chức, danh sách thành viên và con trỏ đến hội đồng tiếp theo trong danh sách.
- `Khoa`: Lưu trữ thông tin về một khoa, bao gồm con trỏ đến đầu danh sách giảng viên, số lượng giảng viên và con trỏ đến đầu danh sách hội đồng.

## Các hàm chính

Chương trình sử dụng các hàm chính sau:

- `themThanhVienVaoKhoa`: Thêm một giảng viên vào danh sách giảng viên của một khoa.
- `timGiaoThoiGianRanh`: Tìm giao của thời gian rảnh của 3 giảng viên.
- `kiemTraTrungLich`: Kiểm tra xem hai hội đồng có trùng lịch tổ chức hay không.
- `taoHoiDong`: Tạo một hội đồng từ 3 giảng viên và thêm hội đồng này vào danh sách hội đồng của một khoa.
- `timKiemHoiDongTheoGiangVien`: Tìm kiếm hội đồng theo tên giảng viên.
- `hienThiThoiGianBieu`: Hiển thị thời gian biểu của tất cả các hội đồng.

## Cách sử dụng

Khi chạy chương trình, người dùng sẽ được yêu cầu nhập thông tin về thời gian rảnh của giảng viên. Sau đó, chương trình sẽ tự động tạo hội đồng dựa trên thông tin này.

Người dùng cũng có thể chọn kiểm tra xem hai hội đồng bất kỳ có trùng lịch tổ chức hay không, tìm kiếm hội đồng theo tên giảng viên, hoặc hiển thị thời gian biểu của tất cả các hội đồng.

## Trường hợp đặc biệt đã xử lý

1. Trùng lịch: Chương trình đã xử lý trường hợp hai hội đồng có thể tổ chức cùng một thời điểm. Trước khi thêm một hội đồng mới vào danh sách, chương trình sẽ kiểm tra xem thời gian tổ chức của hội đồng mới có trùng với thời gian tổ chức của bất kỳ hội đồng nào khác trong cùng một khoa hay không. Nếu có, hội đồng mới sẽ không được thêm vào danh sách.

2. Thời gian rảnh: Chương trình yêu cầu người dùng nhập thời gian rảnh của mỗi giảng viên. Nếu người dùng nhập một khoảng thời gian không hợp lệ (ví dụ, giờ bắt đầu lớn hơn giờ kết thúc), chương trình sẽ yêu cầu người dùng nhập lại.

3. Tìm kiếm hội đồng: Khi tìm kiếm hội đồng theo tên giảng viên, nếu không tìm thấy giảng viên trong danh sách, chương trình sẽ thông báo rằng không tìm thấy giảng viên.

## Quy ước trong code

1. Thứ trong tuần: Thứ 2 được biểu diễn bằng số 2, thứ 3 bằng số 3, v.v., và thứ 7 bằng số 7. Thứ 2 có chỉ số 0 trong danh sách thời gian rảnh, thứ 3 có chỉ số 1, v.v.

2. Giờ trong ngày: Giờ trong ngày được biểu diễn bằng số nguyên từ 0 đến 23, với 0 tượng trưng cho 12 giờ đêm và 23 tượng trưng cho 11 giờ tối.

3. Khoa: Khoa được biểu diễn bằng số nguyên từ 1 đến 7, với 1 tượng trưng cho "Khoa Công nghệ thông tin", 2 tượng trưng cho "Khoa Luật", v.v., và 7 tượng trưng cho "Khoa Thư viện – Văn phòng".

4. Giảng viên: Mỗi giảng viên trong một khoa được biểu diễn bằng một số nguyên, với số nguyên đầu tiên tượng trưng cho giảng viên đầu tiên được thêm vào danh sách của khoa.

## TEST CASE

1. Không có thời gian rảnh của các giảng viên giao nhau để tạo hội đồng:

   - Chọn khoa: 1 (Khoa Công nghệ Thông tin)
   - Chọn giảng viên: 1
     - Thứ 2: nhập thời gian từ 8h đến 10h
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 2
     - Thứ 2: nhập thời gian từ 12h đến 13h, từ 15h đến 18h
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 3
     - Thứ 2: nhập thời gian từ 14h đến 16h
     - Bỏ qua các thứ còn lại (-2)
   - Kết quả: Chương trình sẽ thông báo không thể tạo hội đồng vì không có thời gian rảnh chung giữa các giảng viên.

2. Có thời gian rảnh của các giảng viên giao nhau để tạo hội đồng:

   - Chọn khoa: 1 (Khoa Công nghệ Thông tin)
   - Chọn giảng viên: 1
     - Thứ 2: nhập thời gian từ 8h đến 10h
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 2
     - Thứ 2: nhập thời gian từ 9h đến 11h
     - Bỏ qua các thứ còn lại (-2)
   - Chọn giảng viên tiếp theo: 3
     - Thứ 2: nhập thời gian từ 8h30 đến 9h30
     - Bỏ qua các thứ còn lại (-2)
   - Kết quả: Chương trình sẽ tạo hội đồng với thời gian từ 9h đến 9h30 vào thứ 2.


