// Placeholder data
// When backend ready replace loadData() with fetch() calls and have the add / complete handlers send requests to the backend.

(function () {
  "use strict";

  // ---------- Helpers ----------
  function startOfToday() {
    const d = new Date();
    return new Date(d.getFullYear(), d.getMonth(), d.getDate());
  }

  function toISO(date) {
    const m = String(date.getMonth() + 1).padStart(2, "0");
    const d = String(date.getDate()).padStart(2, "0");
    return date.getFullYear() + "-" + m + "-" + d;
  }

  function daysFromNow(n) {
    const d = startOfToday();
    d.setDate(d.getDate() + n);
    return toISO(d);
  }

  // Parse "YYYY-MM-DD" as a local date (avoids timezone shifts)
  function parseDate(iso) {
    const parts = iso.split("-").map(Number);
    return new Date(parts[0], parts[1] - 1, parts[2]);
  }

  function daysUntil(iso) {
    return Math.round((parseDate(iso) - startOfToday()) / 86400000);
  }

  function formatDate(iso) {
    return parseDate(iso).toLocaleDateString(undefined, {
      weekday: "short", month: "short", day: "numeric"
    });
  }

  function escapeHTML(str) {
    const div = document.createElement("div");
    div.textContent = str;
    return div.innerHTML;
  }

  const PRIORITY_RANK = { High: 0, Medium: 1, Low: 2 };

  // ---------- Placeholder data ----------
  let courses = [];
  let assignments = [];
  let nextId = 1;

  function loadData() {
    courses = [
      { id: 1, code: "CS 101", name: "Intro to Programming" },
      { id: 2, code: "MATH 201", name: "Calculus II" },
      { id: 3, code: "ENG 110", name: "College Writing" },
      { id: 4, code: "BIO 120", name: "General Biology" }
    ];

    assignments = [
      { id: 1, courseId: 1, title: "Lab 4: Loops and Arrays", description: "", dueDate: daysFromNow(-2), priority: "High", completed: false },
      { id: 2, courseId: 2, title: "Problem Set 6", description: "", dueDate: daysFromNow(1), priority: "High", completed: false },
      { id: 3, courseId: 3, title: "Essay Draft 2", description: "", dueDate: daysFromNow(3), priority: "Medium", completed: false },
      { id: 4, courseId: 4, title: "Chapter 5 Quiz", description: "", dueDate: daysFromNow(5), priority: "Low", completed: false },
      { id: 5, courseId: 1, title: "Midterm Project Proposal", description: "", dueDate: daysFromNow(12), priority: "Medium", completed: false },
      { id: 6, courseId: 2, title: "Exam 2", description: "", dueDate: daysFromNow(16), priority: "High", completed: false },
      { id: 7, courseId: 3, title: "Reading Response 3", description: "", dueDate: daysFromNow(-6), priority: "Low", completed: true },
      { id: 8, courseId: 4, title: "Lab Report 1", description: "", dueDate: daysFromNow(-9), priority: "Medium", completed: true }
    ];

    nextId = assignments.length + 1;
  }

  // ---------- Derived state ----------
  function statusOf(a) {
    if (a.completed) return "completed";
    const d = daysUntil(a.dueDate);
    if (d < 0) return "overdue";
    return "upcoming";
  }

  function courseOf(a) {
    return courses.find(function (c) { return c.id === a.courseId; });
  }

  // ---------- DOM refs ----------
  const $ = function (id) { return document.getElementById(id); };

  const els = {
    todayLabel: $("today-label"),
    statUpcoming: $("stat-upcoming"),
    statOverdue: $("stat-overdue"),
    statHigh: $("stat-high"),
    statCompleted: $("stat-completed"),
    filterCourse: $("filter-course"),
    filterPriority: $("filter-priority"),
    filterStatus: $("filter-status"),
    sortBy: $("sort-by"),
    resetFilters: $("reset-filters"),
    activeList: $("active-list"),
    activeEmpty: $("active-empty"),
    activeCount: $("active-count"),
    completedList: $("completed-list"),
    completedEmpty: $("completed-empty"),
    completedCount: $("completed-count"),
    addBtn: $("add-btn"),
    addDialog: $("add-dialog"),
    addForm: $("add-form"),
    cancelBtn: $("cancel-btn"),
    newTitle: $("new-title"),
    newCourse: $("new-course"),
    newDue: $("new-due"),
    newPriority: $("new-priority"),
    newDesc: $("new-desc"),
    logoutBtn: $("logout-btn")
  };

  // ---------- Rendering ----------
  function populateCourseSelects() {
    const filterValue = els.filterCourse.value || "all";

    els.filterCourse.innerHTML = '<option value="all">All courses</option>' +
      courses.map(function (c) {
        return '<option value="' + c.id + '">' + escapeHTML(c.code) + "</option>";
      }).join("");
    els.filterCourse.value = filterValue;

    els.newCourse.innerHTML = courses.map(function (c) {
      return '<option value="' + c.id + '">' + escapeHTML(c.code + " - " + c.name) + "</option>";
    }).join("");
  }

  function getFiltered() {
    const course = els.filterCourse.value;
    const priority = els.filterPriority.value;
    const status = els.filterStatus.value;

    return assignments.filter(function (a) {
      if (course !== "all" && String(a.courseId) !== course) return false;
      if (priority !== "all" && a.priority !== priority) return false;
      if (status !== "all" && statusOf(a) !== status) return false;
      return true;
    });
  }

  function sortList(list) {
    const mode = els.sortBy.value;
    return list.slice().sort(function (a, b) {
      if (mode === "priority") {
        return PRIORITY_RANK[a.priority] - PRIORITY_RANK[b.priority] ||
          a.dueDate.localeCompare(b.dueDate);
      }
      if (mode === "course") {
        return courseOf(a).code.localeCompare(courseOf(b).code) ||
          a.dueDate.localeCompare(b.dueDate);
      }
      return a.dueDate.localeCompare(b.dueDate);
    });
  }

  function dueText(a) {
    if (a.completed) return "Due " + formatDate(a.dueDate);
    const d = daysUntil(a.dueDate);
    if (d < 0) return "Overdue by " + Math.abs(d) + (Math.abs(d) === 1 ? " day" : " days");
    if (d === 0) return "Due today";
    if (d === 1) return "Due tomorrow";
    return "Due " + formatDate(a.dueDate);
  }

  function taskHTML(a) {
    const course = courseOf(a);
    const classes = ["task"];
    if (a.completed) {
      classes.push("done");
    } else {
      const d = daysUntil(a.dueDate);
      if (d < 0) classes.push("overdue");
      else if (d <= 2) classes.push("soon");
    }

    return (
      '<li class="' + classes.join(" ") + '">' +
        '<input type="checkbox" data-id="' + a.id + '"' + (a.completed ? " checked" : "") +
          ' aria-label="Mark ' + escapeHTML(a.title) + ' as completed">' +
        '<div class="task-main">' +
          '<div class="task-title">' + escapeHTML(a.title) + "</div>" +
          '<div class="task-meta">' + escapeHTML(course.code) + " &middot; " + escapeHTML(course.name) + "</div>" +
        "</div>" +
        '<span class="badge badge-' + a.priority + '">' + a.priority + "</span>" +
        '<span class="task-due">' + dueText(a) + "</span>" +
      "</li>"
    );
  }

  function renderStats() {
    let upcoming = 0, overdue = 0, high = 0, completed = 0;
    assignments.forEach(function (a) {
      if (a.completed) { completed++; return; }
      const d = daysUntil(a.dueDate);
      if (d < 0) overdue++;
      else if (d <= 7) upcoming++;
      if (a.priority === "High") high++;
    });
    els.statUpcoming.textContent = upcoming;
    els.statOverdue.textContent = overdue;
    els.statHigh.textContent = high;
    els.statCompleted.textContent = completed;
  }

  function render() {
    renderStats();

    const filtered = sortList(getFiltered());
    const active = filtered.filter(function (a) { return !a.completed; });
    const done = filtered.filter(function (a) { return a.completed; });

    els.activeList.innerHTML = active.map(taskHTML).join("");
    els.completedList.innerHTML = done.map(taskHTML).join("");

    els.activeCount.textContent = active.length;
    els.completedCount.textContent = done.length;
    els.activeEmpty.hidden = active.length > 0;
    els.completedEmpty.hidden = done.length > 0;
  }

  // ---------- Events ----------
  function onToggle(e) {
    if (e.target.type !== "checkbox") return;
    const id = Number(e.target.dataset.id);
    const a = assignments.find(function (x) { return x.id === id; });
    if (!a) return;
    a.completed = e.target.checked;
    // TODO: send update to backend (e.g., PUT /api/assignments/{id})
    render();
  }

  function openAddDialog() {
    els.addForm.reset();
    els.newDue.value = daysFromNow(7);
    els.addDialog.showModal();
    els.newTitle.focus();
  }

  function onAddSubmit(e) {
    e.preventDefault();
    const title = els.newTitle.value.trim();
    if (!title || !els.newDue.value) return;

    assignments.push({
      id: nextId++,
      courseId: Number(els.newCourse.value),
      title: title,
      description: els.newDesc.value.trim(),
      dueDate: els.newDue.value,
      priority: els.newPriority.value,
      completed: false
    });
    // TODO: send new assignment to backend (e.g., POST /api/assignments)

    els.addDialog.close();
    render();
  }
function deleteAssignment(id) {
    assignments = assignments.filter(function (assignment) {
        return assignment.id !== id;
    });

    render();
}
  function resetFilters() {
    els.filterCourse.value = "all";
    els.filterPriority.value = "all";
    els.filterStatus.value = "all";
    els.sortBy.value = "due";
    render();
  }

  function init() {
    loadData();
    populateCourseSelects();

    els.todayLabel.textContent = new Date().toLocaleDateString(undefined, {
      weekday: "long", year: "numeric", month: "long", day: "numeric"
    });

    [els.filterCourse, els.filterPriority, els.filterStatus, els.sortBy].forEach(function (el) {
      el.addEventListener("change", render);
    });
    els.resetFilters.addEventListener("click", resetFilters);
    els.activeList.addEventListener("change", onToggle);
    els.completedList.addEventListener("change", onToggle);
    els.addBtn.addEventListener("click", openAddDialog);
    els.cancelBtn.addEventListener("click", function () { els.addDialog.close(); });
    els.addForm.addEventListener("submit", onAddSubmit);
    els.logoutBtn.addEventListener("click", function () {
      // TODO: call backend logout, then redirect to login page
      alert("Logout will be connected once user accounts are implemented.");
    });

    render();
  }

  init();
})();
