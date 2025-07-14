let mode = document.getElementById("mode-toggle");

mode.addEventListener("click", () => {
  document.body.classList.toggle("light-mode");

  if (document.body.classList.contains("light-mode")) {
    mode.textContent = "🌙Mode";
  } else {
    mode.textContent = "☀️Mode";
  }
});

function openLogin() {
  openLoginModal();
  showAuthForm('login');
}


function openLoginModal() {
  document.getElementById("authModal").style.display = "flex";
}

function closeLoginModal() {
  document.getElementById("authModal").style.display = "none";
}

function showAuthForm(formType) {
  const loginForm = document.getElementById("loginForm");
  const signupForm = document.getElementById("signupForm");
  const loginTab = document.getElementById("loginTab");
  const signupTab = document.getElementById("signupTab");

  if (formType === "login") {
    loginForm.style.display = "block";
    signupForm.style.display = "none";
    loginTab.classList.add("active-tab");
    signupTab.classList.remove("active-tab");
  } else {
    loginForm.style.display = "none";
    signupForm.style.display = "block";
    signupTab.classList.add("active-tab");
    loginTab.classList.remove("active-tab");
  }
}

// Optional: Login handler
document.getElementById("loginForm").addEventListener("submit", function (e) {
  e.preventDefault();
  alert("Login successful!");
  closeLoginModal();
});


// Booking Form Submit
document.getElementById("carBookingForm").addEventListener("submit", function (e) {
  e.preventDefault();

  // Get input values
  const fullName = document.getElementById("fullName").value.trim();
  const email = document.getElementById("bookingEmail").value.trim();
  const carModel = document.getElementById("carModel").value.trim();
  const pickupDate = document.getElementById("pickupDate").value;
  const returnDate = document.getElementById("returnDate").value;

  const confirmationBox = document.getElementById("bookingConfirmation");

  // Basic validation
  if (!fullName || !email || !carModel || !pickupDate || !returnDate) {
    confirmationBox.textContent = "❌ Please fill in all required fields.";
    confirmationBox.style.color = "red";
    return;
  }

  // Check date logic
  if (new Date(pickupDate) > new Date(returnDate)) {
    confirmationBox.textContent = "❌ Return date must be after pickup date.";
    confirmationBox.style.color = "red";
    return;
  }

  // Show success message
  confirmationBox.textContent = `✅ Thank you, Your booking for ${carModel} from ${pickupDate} to ${returnDate} has been received.`;
  confirmationBox.style.color = "lightgreen";

  // Optional: Reset form
  this.reset();
});



document.querySelector('.contact-form').addEventListener('submit', function(e) {
  e.preventDefault();
  document.getElementById('contactMessage').textContent = "Thanks! We will get back to you soon.";
});
