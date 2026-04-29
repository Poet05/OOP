import streamlit as st
import subprocess
import os

st.title("Giao diện cho file sieuthi.cpp 🚀")

# 1. Biên dịch file C++ thành file chạy được (chỉ làm 1 lần)
if not os.path.exists('./sieuthi'):
    with st.spinner("Đang biên dịch mã C++..."):
        # Lệnh: g++ sieuthi.cpp -o sieuthi
        compile_result = subprocess.run(['g++', 'sieuthi.cpp', '-o', 'sieuthi'], capture_output=True, text=True)
        
        if compile_result.returncode != 0:
            st.error("❌ Lỗi khi biên dịch C++:")
            st.code(compile_result.stderr)
            st.stop() # Dừng chương trình nếu lỗi

# 2. Tạo nút bấm để chạy chương trình C++
st.success("✅ Đã biên dịch C++ thành công!")

if st.button("Chạy chương trình C++"):
    with st.spinner("Đang chạy..."):
        # Chạy file vừa biên dịch
        run_result = subprocess.run(['./sieuthi'], capture_output=True, text=True)
        
        # In kết quả ra màn hình web
        st.write("### Kết quả từ C++:")
        st.code(run_result.stdout)
