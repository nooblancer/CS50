-- Keep a log of any SQL queries you execute as you solve the mystery.

.tables --check which tables are there

.schema crime_scene_reports --understanding crime scene formate
SELECT * FROM crime_scene_reports limit 5; --better understanding

SELECT * FROM crime_scene_reports WHERE
    street = 'Humphrey Street';
--searching for the crime
SELECT description FROM crime_scene_reports WHERE
    street = 'Humphrey Street'
    AND day = 28 AND month = 7;
--more filters
--found id = 295, time = 10:15AM
--found that all witnesses mentioned the bakery

.schema bakery_security_logs --understanding what is bakery logs
SELECT * FROM bakery_security_logs LIMIT 5; --better understanding

SELECT * FROM bakery_security_logs WHERE
    day = 28
    AND month = 7
    AND hour = 10
    AND minute = 15;
--searching what happened at the bakery at time of robbery
--found nothing

SELECT * FROM bakery_security_logs WHERE
    day = 28
    AND month = 7
    AND hour = 10;
--less filters


--cmd to find all those who came before the robbery
SELECT license_plate FROM bakery_security_logs WHERE
    day = 28
    AND month = 7
    AND activity = 'entrance'
    AND hour <= 10
    AND minute <= 15;

--cnd to find all those who left after the robbery
SELECT license_plate FROM bakery_security_logs WHERE
    day = 28
    AND month = 7
    AND activity = 'exit'
    AND hour >= 10
    AND minute >= 15;

--cmd for those who came before the robbery, and left after it
SELECT * FROM bakery_security_logs WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs WHERE
        day = 28
        AND month = 7
        AND activity = 'entrance'
        AND hour <= 10
        AND minute <= 15
)
AND (
    SELECT license_plate FROM bakery_security_logs WHERE
        day = 28
        AND month = 7
        AND activity = 'exit'
        AND hour >= 10
        AND minute >= 15
)
    AND day = 28
    AND month = 7
ORDER BY license_plate;

.schema people --understanding what is inside people
SELECT * FROM people LIMIT 5; --better understanding
--found license_plate

.schema interviews -- understanding the interviews
--found id
--not the same as crime id (bruh)

SELECT * FROM interviews WHERE day = 28 AND month = 7;
--ids 161,162,163 talk about the bakery robbery
--161 - Ruth    - saw thief leave in a car within 10 mins (rechecked the time on bakery_security_logs)
--162 - Eugene  - recognized the thief - saw withdraw cash at ATM on 'Leggett Street'
--163 - Raymond - heard the thief on call - earliest flight out of Fifityville tomorrow (29/07) - acomplice bought the ticket

--according to 161-Ruth fresh suspects
SELECT license_plate FROM bakery_security_logs WHERE
    day = 28
    AND month = 7
    AND activity = 'exit'
    AND hour = 10
    AND minute <= 25;

--details about them
SELECT * FROM people WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs WHERE
        day = 28
        AND month = 7
        AND activity = 'exit'
        AND hour = 10
        AND minute <= 25
);

--162: checking ATMS for 28/07
.schema atm_transactions

SELECT * FROM atm_transactions LIMIT 5;

--another list of suspects
SELECT * FROM atm_transactions WHERE
    day = 28
    AND month = 7
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw';

.schema bank_accounts --links account numbers to people(id)

--find people who own those bank accounts
SELECT person_id FROM bank_accounts
WHERE account_number IN (
    SELECT account_number FROM atm_transactions
    WHERE day = 28
    AND month = 7
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw'
);

--finding names
SELECT * FROM people
WHERE id IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE day = 28
        AND month = 7
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
    )
);

--filtering out with license plates
SELECT * FROM people
WHERE id IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE day = 28
        AND month = 7
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
    )
)
AND license_plate IN (
    SELECT license_plate FROM bakery_security_logs WHERE
        day = 28
        AND month = 7
        AND activity = 'exit'
        AND hour = 10
        AND minute <= 25
);

--163 (aayye same line) says they heard the thief on call
.schema phone_calls
SELECT * FROM phone_calls WHERE month = 7 AND day = 28;

--filtering with phone numbers of suspects
SELECT * FROM phone_calls
WHERE month = 7
AND day = 28
AND caller IN (
    SELECT phone_number FROM people
    WHERE id IN (
        SELECT person_id FROM bank_accounts
        WHERE account_number IN (
            SELECT account_number FROM atm_transactions
            WHERE day = 28
            AND month = 7
            AND atm_location = 'Leggett Street'
            AND transaction_type = 'withdraw'
        )
    )
    AND license_plate IN (
        SELECT license_plate FROM bakery_security_logs WHERE
            day = 28
            AND month = 7
            AND activity = 'exit'
            AND hour = 10
            AND minute <= 25
    )
);
--apparantly only two of our suspects made a call that whole day
--Brunce made 4 calls
--Diana made 1 call to Philip

--looking for flight data
.schema flights
SELECT * FROM flights WHERE day = 29 AND month = 7 ORDER BY hour; --as the thief took the first flight a day after robbery
--all flights are from airport 8
--first flight left for 4

.schema airports
SELECT * FROM airports WHERE city = 'Fiftyville'; --fiftyville is 8!!
--4 is NYC!

.schema passengers
SELECT * FROM passengers WHERE flight_id = 36;


--filtering with all the available data
SELECT * FROM people
WHERE passport_number IN (
    SELECT passport_number FROM passengers WHERE flight_id = 36
)
AND phone_number IN (
    SELECT caller FROM phone_calls
    WHERE month = 7
    AND day = 28
    AND caller IN (
        SELECT phone_number FROM people
        WHERE id IN (
            SELECT person_id FROM bank_accounts
            WHERE account_number IN (
                SELECT account_number FROM atm_transactions
                WHERE day = 28
                AND month = 7
                AND atm_location = 'Leggett Street'
                AND transaction_type = 'withdraw'
            )
        )
        AND license_plate IN (
            SELECT license_plate FROM bakery_security_logs WHERE
                day = 28
                AND month = 7
                AND activity = 'exit'
                AND hour = 10
                AND minute <= 25
        )
    )
);
--IT IS BRUCE!!!
--|   id   | name  |  phone_number  | passport_number | license_plate |
--+--------+-------+----------------+-----------------+---------------+
--| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |

--FINDING THE ACCOMPLICE!
--suspects:
SELECT * FROM people
WHERE phone_number IN (
    SELECT receiver FROM phone_calls
    WHERE month = 7
    AND day = 28
    AND caller = '(367) 555-5533'
);

--can't find shit on the accomplice!
--went back to interviews
--163: BRUCE TALKED TO THE ACCOMPLICE FOR LESS THAN A MINUTE!!

--checking the calls
SELECT * FROM phone_calls
WHERE month = 7
AND day = 28
AND caller = '(367) 555-5533'
ORDER BY duration;
--only talked to one person for less than a minute!!

SELECT * FROM people
WHERE phone_number = "(375) 555-8161";

--ROBIN IS BUSTED!
