<?php

/**
 * Class EntityGroupController
 */
class EntityGroupController {

  /**
   * @var string $groupType
   *   The group type for this entity group controller.
   */
  protected $groupType;

  /**
   * @var array $groupInfo
   *   The group type info.
   */
  protected $groupInfo;

  /**
   * @var array $structure
   *   The group structure.
   */
  protected $structure;

  /**
   * @var \EntityGroup $group
   *   The group being controlled.
   */
  protected $group;

  /**
   * @var string $rootPath
   *   The menu item path to access the group entities.
   */
  protected $rootPath;

  /**
   * @var string[] $fieldCategoryGroups
   */
  protected $fieldCategoryGroups;

  /**
   * @var array $fieldCategories
   */
  protected $fieldCategories;

  /**
   * EntityGroup constructor.
   *
   * @param string $group_type
   *   The group type.
   */
  public function __construct($group_type) {
	$this->groupType = $group_type;
	$this->groupInfo = entity_toolbox_entity_group_get_info($group_type);
  }

  /**
   * Returns the group type.
   *
   * @return string
   */
  public function groupType() {
	return $this->groupType;
  }

  /**
   * Returns the group info.
   *
   * @return array
   */
  public function groupInfo() {
	return $this->groupInfo;
  }

  /**
   * Returns the menu item path to access the group entities.
   *
   * @return string
   */
  public function rootPath() {
	return $this->groupInfo['path'];
  }

  /**
   * Returns the field category groups.
   *
   * @return string[]
   *
   * @see hook_entity_toolbox_field_category_group_info().
   */
  public function fieldCategoryGroups() {
	return $this->groupInfo['field_category_groups'];
  }

  /**
   * Retrieves the fields categories available for this entity group.
   */
  protected function setFieldCategories() {
	foreach ($this->fieldCategoryGroups() as $group) {
	  $group_info                    = entity_toolbox_field_category_group_get_info($group);
	  $this->fieldCategories[$group] = $group_info['field_categories'];
	}
  }

  /**
   * Returns the field categories of the group.
   *
   * @param string $field_category_group
   *   The field category group of the categories.
   *
   * @return string[]
   */
  public function fieldCategories($field_category_group) {
	return $this->fieldCategories[$field_category_group];
  }
}