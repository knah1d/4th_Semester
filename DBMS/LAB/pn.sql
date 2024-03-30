
drop table pn;
drop table pn2;

create table pn (
    phone_no varchar2(20),
    constraint pk_pn primary key(phone_no)
);
insert into pn values('8006330575');
insert into pn values('8006330576');
insert into pn values('8006330577');
create table pn2 (
    phone_no varchar2(20),
    constraint pk_pn2 primary key(phone_no)
);

create or replace procedure format_phone 
  (phone_no in out varchar2) is
begin 
  phone_no := '(' || substr(phone_no, 1, 3) ||
              ')' || substr(phone_no, 4, 3) ||
              '-' || substr(phone_no, 7);
  --select phone_no from pn;
  end format_phone;
/

set serveroutput on;


declare
  cursor phone_curs is
    select phone_no from pn; 
begin
  for rec in phone_curs loop
    format_phone(rec.phone_no); 
    insert into pn2 values(rec.phone_no)
    dbms_output.put_line('Formatted Phone Number: ' || rec.phone_no);
  end loop;
end;
/

