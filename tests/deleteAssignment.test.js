function deleteAssignment(assignments, id) {
    return assignments.filter(function (assignment) {
        return assignment.id !== id;
    });
}

test("deleteAssignment removes the selected task", () => {
    const assignments = [
        { id: 1, title: "Math Homework" },
        { id: 2, title: "Algorithms Homework" }
    ];

    const result = deleteAssignment(assignments, 1);

    expect(result.length).toBe(1);
    expect(result[0].id).toBe(2);
});