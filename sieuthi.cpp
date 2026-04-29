#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <memory>
#include <ctime>

using namespace std;

// ============================================================
// BASE CLASS: SanPham — đa hình (polymorphism)
// ============================================================
class SanPham
{
protected:
    string maSP;
    string tenSP;
    double giaBan;
    int soLuongTon;
    string danhMuc;

public:
    SanPham(string ma, string ten, double gia, int sl, string dm)
        : maSP(ma), tenSP(ten), giaBan(gia), soLuongTon(sl), danhMuc(dm) {}

    virtual ~SanPham() {}

    // Hàm thuần ảo — bắt buộc lớp con override
    virtual void hienThi() const = 0;
    virtual double tinhThue() const = 0;
    virtual string loaiSP() const = 0;

    string getMaSP() const { return maSP; }
    string getTenSP() const { return tenSP; }
    double getGiaBan() const { return giaBan; }
    int getSoLuong() const { return soLuongTon; }
    string getDanhMuc() const { return danhMuc; }

    void setGiaBan(double gia) { giaBan = gia; }
    void setSoLuong(int sl) { soLuongTon = sl; }

    double giaSauThue() const { return giaBan * (1 + tinhThue()); }

    bool capNhatTon(int soLuong)
    {
        if (soLuongTon >= soLuong)
        {
            soLuongTon -= soLuong;
            return true;
        }
        return false;
    }
};

// ============================================================
// LỚP CON: ThucPham
// ============================================================
class ThucPham : public SanPham
{
private:
    string ngayHetHan;
    bool canLanh;

public:
    ThucPham(string ma, string ten, double gia, int sl, string hh, bool lanh)
        : SanPham(ma, ten, gia, sl, "Thực phẩm"), ngayHetHan(hh), canLanh(lanh) {}

    double tinhThue() const override { return 0.05; }
    string loaiSP() const override { return "Thực phẩm"; }

    void hienThi() const override
    {
        cout << left
             << setw(10) << maSP
             << setw(28) << tenSP
             << setw(16) << loaiSP()
             << setw(14) << fixed << setprecision(0) << giaBan
             << setw(8) << soLuongTon
             << "HSD: " << ngayHetHan
             << (canLanh ? " | Can lanh" : "") << "\n";
    }
};

// ============================================================
// LỚP CON: HangTieuDung
// ============================================================
class HangTieuDung : public SanPham
{
private:
    string thuongHieu;
    string xuatXu;

public:
    HangTieuDung(string ma, string ten, double gia, int sl, string th, string xx)
        : SanPham(ma, ten, gia, sl, "Tieu dung"), thuongHieu(th), xuatXu(xx) {}

    double tinhThue() const override { return 0.10; }
    string loaiSP() const override { return "Hang tieu dung"; }

    void hienThi() const override
    {
        cout << left
             << setw(10) << maSP
             << setw(28) << tenSP
             << setw(16) << loaiSP()
             << setw(14) << fixed << setprecision(0) << giaBan
             << setw(8) << soLuongTon
             << thuongHieu << " | " << xuatXu << "\n";
    }
};

// ============================================================
// LỚP CON: DienTu
// ============================================================
class DienTu : public SanPham
{
private:
    int baoHanhThang;
    string model;

public:
    DienTu(string ma, string ten, double gia, int sl, int bh, string mod)
        : SanPham(ma, ten, gia, sl, "Dien tu"), baoHanhThang(bh), model(mod) {}

    double tinhThue() const override { return 0.08; }
    string loaiSP() const override { return "Dien tu"; }

    void hienThi() const override
    {
        cout << left
             << setw(10) << maSP
             << setw(28) << tenSP
             << setw(16) << loaiSP()
             << setw(14) << fixed << setprecision(0) << giaBan
             << setw(8) << soLuongTon
             << "Model: " << model << " | BH: " << baoHanhThang << " thang\n";
    }
};

// ============================================================
// CLASS: KhachHang
// ============================================================
class KhachHang
{
public:
    enum HangThe
    {
        THUONG,
        BACH_KIM,
        VANG,
        KIM_CUONG
    };

private:
    string maKH;
    string hoTen;
    string soDT;
    double tongChiTieu;
    HangThe hangThe;

    HangThe xepHang() const
    {
        if (tongChiTieu >= 50000000)
            return KIM_CUONG;
        if (tongChiTieu >= 20000000)
            return VANG;
        if (tongChiTieu >= 5000000)
            return BACH_KIM;
        return THUONG;
    }

public:
    KhachHang(string ma, string ten, string dt)
        : maKH(ma), hoTen(ten), soDT(dt), tongChiTieu(0), hangThe(THUONG) {}

    string getMaKH() const { return maKH; }
    string getHoTen() const { return hoTen; }

    string tenHang() const
    {
        switch (hangThe)
        {
        case BACH_KIM:
            return "Bach Kim (3%)";
        case VANG:
            return "Vang (5%)";
        case KIM_CUONG:
            return "Kim Cuong (10%)";
        default:
            return "Thuong (0%)";
        }
    }

    double tyLeGiamGia() const
    {
        switch (hangThe)
        {
        case BACH_KIM:
            return 0.03;
        case VANG:
            return 0.05;
        case KIM_CUONG:
            return 0.10;
        default:
            return 0.0;
        }
    }

    void capNhatChiTieu(double soTien)
    {
        tongChiTieu += soTien;
        hangThe = xepHang();
    }

    void hienThi() const
    {
        cout << left
             << setw(10) << maKH
             << setw(25) << hoTen
             << setw(15) << soDT
             << setw(20) << tenHang()
             << fixed << setprecision(0) << tongChiTieu << " VND\n";
    }
};

// ============================================================
// CLASS: ChiTietHoaDon
// ============================================================
struct ChiTietHoaDon
{
    shared_ptr<SanPham> sanPham;
    int soLuong;
    double donGia;

    double thanhTien() const { return donGia * soLuong; }
};

// ============================================================
// CLASS: HoaDon
// ============================================================
class HoaDon
{
private:
    static int demHD;
    string maHD;
    string ngayLap;
    KhachHang *khachHang;
    vector<ChiTietHoaDon> chiTiet;

    string taoNgay() const
    {
        time_t t = time(nullptr);
        tm *now = localtime(&t);
        char buf[20];
        strftime(buf, sizeof(buf), "%d/%m/%Y", now);
        return string(buf);
    }

public:
    HoaDon(KhachHang *kh = nullptr) : khachHang(kh)
    {
        maHD = "HD" + to_string(++demHD);
        ngayLap = taoNgay();
    }

    string getMaHD() const { return maHD; }

    bool themSanPham(shared_ptr<SanPham> sp, int soLuong)
    {
        if (!sp->capNhatTon(soLuong))
        {
            cout << "  [!] Khong du hang ton kho!\n";
            return false;
        }
        chiTiet.push_back({sp, soLuong, sp->giaSauThue()});
        return true;
    }

    double tongTien() const
    {
        double tong = 0;
        for (auto &ct : chiTiet)
            tong += ct.thanhTien();
        return tong;
    }

    double tienGiamGia() const
    {
        if (khachHang)
            return tongTien() * khachHang->tyLeGiamGia();
        return 0;
    }

    double thanhToan() const { return tongTien() - tienGiamGia(); }

    void inHoaDon() const
    {
        cout << "\n";
        cout << "=========================================\n";
        cout << "          SIEU THI MINI MART            \n";
        cout << "=========================================\n";
        cout << "Ma HD : " << maHD << "   Ngay: " << ngayLap << "\n";
        if (khachHang)
            cout << "KH    : " << khachHang->getHoTen()
                 << " [" << khachHang->tenHang() << "]\n";
        else
            cout << "KH    : Khach le\n";
        cout << "-----------------------------------------\n";
        cout << left
             << setw(25) << "San pham"
             << setw(6) << "SL"
             << setw(14) << "Don gia (VND)"
             << "Thanh tien\n";
        cout << "-----------------------------------------\n";
        for (auto &ct : chiTiet)
        {
            cout << left
                 << setw(25) << ct.sanPham->getTenSP()
                 << setw(6) << ct.soLuong
                 << setw(14) << fixed << setprecision(0) << ct.donGia
                 << ct.thanhTien() << "\n";
        }
        cout << "-----------------------------------------\n";
        cout << right << setw(47) << "Tong: " << fixed << setprecision(0) << tongTien() << "\n";
        if (tienGiamGia() > 0)
            cout << right << setw(47) << "Giam gia: -" << tienGiamGia() << "\n";
        cout << right << setw(47) << "THANH TOAN: " << thanhToan() << " VND\n";
        cout << "=========================================\n";
        cout << "         Cam on quy khach!\n";
        cout << "=========================================\n\n";
    }

    void capNhatKhachHang()
    {
        if (khachHang)
            khachHang->capNhatChiTieu(thanhToan());
    }
};
int HoaDon::demHD = 0;

// ============================================================
// CLASS: QuanLySieuThi
// ============================================================
class QuanLySieuThi
{
private:
    vector<shared_ptr<SanPham>> dsSanPham;
    vector<KhachHang> dsKhachHang;
    vector<HoaDon> dsHoaDon;
    double doanhThu;

    shared_ptr<SanPham> timSanPham(const string &ma)
    {
        for (auto &sp : dsSanPham)
            if (sp->getMaSP() == ma)
                return sp;
        return nullptr;
    }

    KhachHang *timKhachHang(const string &ma)
    {
        for (auto &kh : dsKhachHang)
            if (kh.getMaKH() == ma)
                return &kh;
        return nullptr;
    }

public:
    QuanLySieuThi() : doanhThu(0) {}

    // --- Them san pham ---
    void themThucPham(string ma, string ten, double gia, int sl, string hh, bool lanh)
    {
        dsSanPham.push_back(make_shared<ThucPham>(ma, ten, gia, sl, hh, lanh));
        cout << "  [+] Da them thuc pham: " << ten << "\n";
    }

    void themHangTieuDung(string ma, string ten, double gia, int sl, string th, string xx)
    {
        dsSanPham.push_back(make_shared<HangTieuDung>(ma, ten, gia, sl, th, xx));
        cout << "  [+] Da them hang tieu dung: " << ten << "\n";
    }

    void themDienTu(string ma, string ten, double gia, int sl, int bh, string mod)
    {
        dsSanPham.push_back(make_shared<DienTu>(ma, ten, gia, sl, bh, mod));
        cout << "  [+] Da them do dien tu: " << ten << "\n";
    }

    // --- Them khach hang ---
    void themKhachHang(string ma, string ten, string dt)
    {
        dsKhachHang.push_back(KhachHang(ma, ten, dt));
        cout << "  [+] Da them khach hang: " << ten << "\n";
    }

    // --- Hien thi kho (GOI DA HINH) ---
    void hienThiKho() const
    {
        cout << "\n=== KHO HANG ===\n";
        cout << left
             << setw(10) << "Ma SP"
             << setw(28) << "Ten san pham"
             << setw(16) << "Loai"
             << setw(14) << "Gia goc (VND)"
             << setw(8) << "Ton kho"
             << "Chi tiet\n";
        cout << string(105, '-') << "\n";
        for (auto &sp : dsSanPham)
            sp->hienThi(); // <-- GOI DA HINH
        cout << "\n";
    }

    // --- Hien thi khach hang ---
    void hienThiKhachHang() const
    {
        cout << "\n=== DANH SACH KHACH HANG ===\n";
        cout << left
             << setw(10) << "Ma KH"
             << setw(25) << "Ho ten"
             << setw(15) << "SDT"
             << setw(20) << "Hang the"
             << "Tong chi tieu\n";
        cout << string(85, '-') << "\n";
        for (auto &kh : dsKhachHang)
            kh.hienThi();
        cout << "\n";
    }

    // --- Tao hoa don ---
    HoaDon *taoHoaDon(const string &maKH = "")
    {
        KhachHang *kh = maKH.empty() ? nullptr : timKhachHang(maKH);
        dsHoaDon.push_back(HoaDon(kh));
        return &dsHoaDon.back();
    }

    bool themVaoHoaDon(HoaDon *hd, const string &maSP, int soLuong)
    {
        auto sp = timSanPham(maSP);
        if (!sp)
        {
            cout << "  [!] Khong tim thay san pham: " << maSP << "\n";
            return false;
        }
        return hd->themSanPham(sp, soLuong);
    }

    void thanhToanHoaDon(HoaDon *hd)
    {
        hd->inHoaDon();
        doanhThu += hd->thanhToan();
        hd->capNhatKhachHang();
    }

    // --- Thong ke ---
    void thongKe() const
    {
        cout << "\n=== THONG KE ===\n";
        cout << "Tong doanh thu    : " << fixed << setprecision(0) << doanhThu << " VND\n";
        cout << "Tong hoa don      : " << dsHoaDon.size() << "\n";
        cout << "Tong san pham     : " << dsSanPham.size() << "\n";
        cout << "Tong khach hang   : " << dsKhachHang.size() << "\n";

        cout << "\nSan pham sap het kho (duoi 5):\n";
        bool co = false;
        for (auto &sp : dsSanPham)
        {
            if (sp->getSoLuong() < 5)
            {
                cout << "  [!] " << sp->getTenSP() << " - con " << sp->getSoLuong() << " cai\n";
                co = true;
            }
        }
        if (!co)
            cout << "  (Khong co)\n";
        cout << "\n";
    }

    // --- Chay demo ---
    void chayDemo()
    {
        // --- Them san pham ---
        cout << ">> Nhap hang vao kho...\n";
        themThucPham("TP001", "Sua tuoi TH True Milk", 28000, 50, "01/12/2025", true);
        themThucPham("TP002", "Banh mi sandwich", 15000, 30, "05/11/2025", false);
        themThucPham("TP003", "Thit bo nhap khau", 250000, 10, "10/11/2025", true);
        themHangTieuDung("TD001", "Dau goi Sunsilk 650ml", 89000, 40, "Unilever", "Viet Nam");
        themHangTieuDung("TD002", "Nuoc rua chen Sunlight", 45000, 3, "Unilever", "Viet Nam");
        themDienTu("DT001", "Tai nghe Sony WH-1000XM5", 7990000, 8, 24, "WH-1000XM5");
        themDienTu("DT002", "Loa Bluetooth JBL Go 3", 890000, 15, 12, "JBL Go 3");

        // --- Them khach hang ---
        cout << "\n>> Dang ky khach hang...\n";
        themKhachHang("KH001", "Nguyen Van An", "0901234567");
        themKhachHang("KH002", "Tran Thi Binh", "0912345678");

        // --- Hien thi kho ---
        hienThiKho();

        // --- Hoa don 1: khach hang co the ---
        cout << ">> Tao hoa don cho khach KH001...\n";
        HoaDon *hd1 = taoHoaDon("KH001");
        themVaoHoaDon(hd1, "TP001", 3);
        themVaoHoaDon(hd1, "TD001", 1);
        themVaoHoaDon(hd1, "DT002", 1);
        thanhToanHoaDon(hd1);

        // --- Hoa don 2: khach le ---
        cout << ">> Tao hoa don khach le...\n";
        HoaDon *hd2 = taoHoaDon();
        themVaoHoaDon(hd2, "TP002", 5);
        themVaoHoaDon(hd2, "TP003", 2);
        thanhToanHoaDon(hd2);

        // --- Thong ke ---
        thongKe();

        // --- Danh sach khach hang ---
        hienThiKhachHang();
    }
};

// ============================================================
// MAIN — Demo chuong trinh
// ============================================================
int main()
{
    cout << "\n";
    cout << "=============================================\n";
    cout << "   CHUONG TRINH QUAN LY SIEU THI (C++)     \n";
    cout << "=============================================\n\n";

    QuanLySieuThi sieuThi;
    sieuThi.chayDemo();

    return 0;
}