-- Keep a log of any SQL queries you execute as you solve the mystery.

--know all the list first
.tables
.schema airports
.schema crime_scene_reports
.schema people
.schema atm_transactions 
.schema flights
.schema phone_calls
.schema bank_accounts
.schema interviews 
.schema courthouse_security_logs
.schema passengers

--draw crime_scene report 
SELECT id, description FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street";

--draw relevant interview report
SELECT name, transcript from interviews WHERE year = 2020 AND month = 7 AND day = 28;

--check ATM_transaction from interview
SELECT id, account_number, transaction_type, amount FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street";

--check courthouse
SELECT activity, license_plate from courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 and minute between 15 and 35; 

-- check phone call
SELECT caller, receiver, duration from phone_calls where year = 2020 AND month = 7 AND day = 28 and duration < 75; 

-- search the earliest flight of 29 July 
select id, hour, minute from flights where year = 2020 AND month = 7 AND day = 29 order by hour;

--dig into bank account
select person_id from bank_accounts where account_number in (select account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street"); 

--try to combine data 
SELECT name, id from people 
where phone_number in (SELECT caller from phone_calls where year = 2020 AND month = 7 AND day = 28 and duration < 60) 
and license_plate in (SELECT license_plate from courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 and minute between 15 and 25) 
and passport_number in (select passport_number from passengers where flight_id = 36) 
and id in (select person_id from bank_accounts where account_number in (select account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" and transaction_type = "withdraw")); 

--find his accomplice
select phone_number from people where id = "686048"; 
select name, id from people where phone_number in (SELECT receiver from phone_calls where year = 2020 AND month = 7 AND day = 28 and caller = "(367) 555-5533" and duration < 75);

select city from airports where id = (select destination_airport_id from flights where id = 36 and year = 2020 AND month = 7 AND day = 29); 