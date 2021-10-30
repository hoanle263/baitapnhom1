#include <stdio.h>
#include <string.h>

struct SinhVien;
void hienThiDSSV(struct SinhVien*, int);
void hienThiTenCot();

struct HoTen {
	char ho[20];
	char dem[21];
	char ten[20];
};

struct DiemSV {
	float diemQT;
    float diemCong;
    float diemTH;
    float diemLT;
    float diemTK;  
};

struct SinhVien {
	char ID[12];
	struct HoTen hoVaTen;
	int tuoi;
	char gioiTinh[10];
	struct DiemSV diem;
	char email[31];
};

void nhapDiem(struct DiemSV* diem) {
	printf("DIem thuc hanh: ");
	scanf("%f", &diem->diemTH);
	printf("Diem ly thuyet: ");
	scanf("%f", &diem->diemLT);
	printf("Diem qua trinh: ");
	scanf("%f", &diem->diemQT);
    printf("Diem cong: ");
    scanf("%d", &diem->diemCong);
	printf("Diem tong ket: ");
	diem -> diemTK = (diem -> diemTH + diem -> diemLT + diem -> diemQT + diem-> diemCong) / 4;
}

void nhapHoTen(struct HoTen* ten) {
	printf("Ho: ");
	scanf("%s", ten->ho);
	printf("Dem: ");
	getchar();
	gets(ten->dem);
	printf("Ten: ");
	scanf("%s", ten->ten);
}

struct SinhVien nhapSV() {
	struct SinhVien sv;
	printf("Nhap ID sinh vien: ");
	scanf("%d", &sv.ID);
	nhapHoTen(&sv.hoVaTen);
	printf("Gioi tinh: ");
	scanf("%s", sv.gioiTinh);
	nhapDiem(&sv.diem);
    printf("Email cua sinh vien: ");
	scanf("%s",sv.email);
	return sv;
}

void hienThiTTSV(struct SinhVien sv) {
	printf("%-10s %-20s %-10s %-10d %-10s \n"
	, sv.hoVaTen.ho, sv.hoVaTen.dem, sv.hoVaTen.ten, sv.tuoi, sv.gioiTinh);
}

void sapXepTheoTen(struct SinhVien* ds, int slsv) {
	int i, j;
	for(i = 0; i < slsv - 1; i++) {
		for(j = slsv - 1; j > i; j --) {
			if(strcmp(ds[j].hoVaTen.ten, ds[j-1].hoVaTen.ten) < 0) {
				struct SinhVien sv = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = sv;
			}
		}
	}
}

void sapXepTheoDiem(struct SinhVien* ds, int slsv) {
	int i, j;
	for(i = 0; i < slsv - 1; i++) {
		for(j = slsv - 1; j > i; j --) {
			if(ds[j].diem.diemTK > ds[j - 1].diem.diemTK) {
				struct SinhVien sv = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = sv;
			}
		}
	}
}

void timTheoTen(struct SinhVien* ds, int slsv) {
	char ten[20];
	printf("Nhap ten: ");
	scanf("%s", ten);
	hienThiTenCot();
	int i, timSV = 0;
	for(i = 0; i < slsv; i++) {
		if(strcmp(ten, ds[i].hoVaTen.ten) == 0) {
			hienThiTTSV(ds[i]);
			timSV = 1;
		}
	}
	if(timSV == 0) {
		printf("Khong co sinh vien %s trong danh sach!\n", ten);
	}
}

void hienThiTenCot() {
	printf("-----------------------------------------------------"
	"----------------------------------------------------------------\n");
	printf("%-5s %-5s %-5s %-5s %-5s %-15s %-15s %-15s %-15s %-5s %-10s\n", 
		"ID", "Ho", "Dem", "Ten", "Tuoi", "Gioi Tinh", 
		"Diem qua trinh", "Diem thuc hanh", "Diem li thuyet", "Diem cong", "Diem tong ket");
}

void hienThiDSSV(struct SinhVien* ds, int slsv) {
	hienThiTenCot();
	int i;
	for(i = 0; i < slsv; i++) {
		hienThiTTSV(ds[i]);
	}
	printf("-----------------------------------------------------"
	"----------------------------------------------------------------\n");
}

int main() {
	struct SinhVien dssv[100];
	int slsv = 0;
	int luaChon;
	printf("DANH SACH SINH VIEN HIEN THOI:\n");
	hienThiDSSV(dssv, slsv);
	int i;
				
	do {
		printf("=============== MENU ===============");
		printf("\n1. Them Sinh vien vao danh sach.");
		printf("\n2. Hien thi danh sach sinh vien.");
		printf("\n3. Sap xep theo ten.");
		printf("\n4. Sap xep theo diem giam dan.");
		printf("\n5. Tim sinh vien theo ten.");
		printf("\n0. Thoat chuong trinh.");
		printf("\nBan chon ? ");
		
		scanf("%d", &luaChon);
		struct SinhVien sv;
		
		switch(luaChon) {
			case 0:
				break;
				
			case 1:
				sv = nhapSV();
				dssv[slsv++] = sv;
				break;
				
			case 2:
				hienThiDSSV(dssv, slsv);
				break;
				
			case 3:
				sapXepTheoTen(dssv, slsv);
				printf("\nDanh sach sinh vien sau khi sap xep theo ten a-z:\n");
				hienThiDSSV(dssv, slsv);
				break;
				
			case 4:
				sapXepTheoDiem(dssv, slsv);
				printf("\nDanh sach sinh vien sau khi sap xep theo diem giam dan:\n");
				hienThiDSSV(dssv, slsv);
				break;
				
			case 5:
				timTheoTen(dssv, slsv);
				break;
				
			default:
				printf("Sai chuc nang, vui long chon lai!\n");
				break;
		}
		
	} while(luaChon);
	
	return 0;
}