import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# export API_KEY=pk_5abea813a7b3486491f1d0e87b49dc91
# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    # ask for log in
    if not session["user_id"]:
        return redirect("/login")
        # if log in, show a HTML table about the current
    else:
        # db.execute("SELECT * FROM ?", session["user_id"])
        # db.execute("SELECT * FROM users")
        # return render_template("index.html", symbol=symbol, share=share, cash=cash)
        return render_template("index.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # requested via get -> display form to buy a stock
    if request.method == "GET":
        return render_template("buy.html")
    # submitted via post -> purchase the stock so long as the user can afford i
    elif request.method == "POST":
        # ask for symbol and number of shares
        symbol = request.form.get("symbol").upper()
        share = request.form.get("shares")

        # check if symbol is valid
        if lookup(symbol) is None:
            return apology("invalid symbol", 400)
        # check if "share" is valid
        elif share.isnumeric() == False or int(share) <= 0 or int(share) != float(share):
            return apology("invalid share", 400)
        else:
            cprice = float(lookup(symbol).get("price"))
            name = "userID" + str(session["user_id"])
            now = datetime.now()

            # check if the stock has been bought before
            buy_check = db.execute(
                "Select * from ? WHERE Symbol=? AND history=0", name, symbol
            )
            if len(buy_check) == 0:
                db.execute(
                    "INSERT INTO ? (Symbol, Share, Time, Price, History) VALUES(?, 0, ?, 0, 0)",
                    name,
                    symbol,
                    now,
                )

            cash_check = db.execute(
                "SELECT * FROM users WHERE id=?", session["user_id"])
            cash = float(cash_check[0]["cash"])

            # check if enough cash
            if cprice * int(share) > cash:
                return apology("Not enough cash", 403)
            else:
                ccash = cash - (cprice * int(share))
                db.execute(
                    "INSERT INTO ? (Symbol, Share, Time, Price, History) VALUES(?, ?, ?, ?, 1)",
                    name,
                    symbol,
                    share,
                    now,
                    cprice,
                )
                # update cash to reflect purchased stock
                db.execute(
                    "UPDATE Users SET cash = ? WHERE id =?", ccash, session["user_id"]
                )
                # run SQL statement for stock history
                db.execute(
                    "UPDATE ? SET Share = share + ? WHERE Symbol=? AND History=0",
                    name,
                    share,
                    symbol,
                )
                share_check = db.execute(
                    "Select * from ? where history = 0 and symbol = ?", name, symbol)
                share_total = share_check[0]["Share"]
                total_price = cprice * share_total
                company_name = str(lookup(symbol).get("name"))

                return render_template("buy2.html", symbol=symbol, company_name=company_name, cprice=cprice, share_total=share_total, total_price=total_price, ccash=ccash)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # display a table with 1. stock symbol 2. buy/sell 3. price at that time 4. date and time that transaction occured
    # check birthdays
    table_name = "userID" + str(session["user_id"])
    user = db.execute("select * from ?", table_name)

    return render_template("history.html", user=user)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get(
                "username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # requested via get -> display form to request a stock quote
    if request.method == "GET":
        return render_template("quote.html")
    # submitted via post -> lookup the stock symbol by calling the lookup function and display the result
    else:
        symbol = request.form.get("symbol").upper()

        if not lookup(symbol):
            return apology("Invalid symbol", 400)
        else:
            name = lookup(symbol).get("name")
            price = float("{:.2f}".format(lookup(symbol).get("price")))
            return render_template("quote2.html", symbol=symbol, name=name, price=price)


@ app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # -check birthdays -
    # when requested via GET, display registration form
    if request.method == "GET":
        return render_template("registration.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirm_password = request.form.get("confirmation")

        # When form is submitted via post, check for possible errors and insert the new user into users table. If error, return 400
        # any field left back
        if not username or not password or not confirm_password:
            return apology("You can't leave any field empty!", 400)
        # password and confirmation didn't match
        elif not (password == confirm_password):
            return apology("Please confirm your password.", 400)
        # username being taken
        elif len(db.execute("SELECT * FROM users WHERE username=?", username)) != 0:
            return apology("The username has been taken.")
        # only store the hashed password
        # log user in
        else:
            hash = generate_password_hash(password)
            db.execute(
                "INSERT INTO users (username, hash) VALUES(?, ?)", username, hash
            )
            # create SQL table for the user
            user_id = db.execute(
                "SELECT * FROM users WHERE username=?", username)
            name = "userID" + str(user_id[0]["id"])
            db.execute(
                "CREATE TABLE ? (id INTEGER, Symbol TEXT NOT NULL, Share INTEGER, Time DATETIME, Price NUMERIC NOT NULL, History BOOL, PRIMARY KEY(id))",
                name,
            )
            return render_template("index.html")


@ app.route("/sell", methods=["GET", "POST"])
@ login_required
def sell():
    """Sell shares of stock"""
    # requested via GET -> display form to sell a stock
    name = "userID" + str(session["user_id"])
    if request.method == "GET":
        users = db.execute("select * from ? where history=0", name)
        return render_template("sell.html", users=users)
    # submitted via post -> sell the stock as long as it is possible
    elif request.method == "POST":
        # ask for symbol and number of shares
        symbol = request.form.get("symbol")
        share = request.form.get("shares")
        cprice = float(lookup(symbol).get("price"))
        # check if symbol is valid
        if not lookup(symbol):
            return apology("invalid symbol", 400)
        if share.isnumeric() == False or int(share) <= 0 or int(share) != float(share):
            return apology("invalid number", 400)

        now = datetime.now()

        # check if enough stock to sell
        share_check = db.execute(
            "Select * from ? where symbol=? and history=0", name, symbol
        )
        if int(share_check[0]["Share"]) < int(share) or len(share_check) == 0:
            return apology("Not enough stock.", 400)
        else:
            cash_check = db.execute(
                "SELECT * FROM users WHERE id=?", session["user_id"]
            )
            cash = float(cash_check[0]["cash"])
            ccash = (cprice * int(share)) + cash
            db.execute(
                "INSERT INTO ? (Symbol, Share, Time, Price, History) VALUES(?, ?, ?, ?, 1)",
                name,
                symbol,
                share * -1,
                now,
                cprice,
            )
            # update cash
            db.execute(
                "UPDATE Users SET cash = ? WHERE id =?", ccash, session["user_id"]
            )
            # run SQL statement for stock history
            db.execute(
                "UPDATE ? SET Share = share - ? WHERE Symbol=? AND History=0",
                name,
                share,
                symbol,
            )
            share_check = db.execute(
                "Select * from ? where history = 0 and symbol = ?", name, symbol)
            share_total = share_check[0]["Share"]
            total_price = cprice * share_total
            company_name = str(lookup(symbol).get("name"))
            return render_template("sell2.html", symbol=symbol, company_name=company_name, cprice=cprice, share_total=share_total, total_price=total_price, ccash=ccash)
