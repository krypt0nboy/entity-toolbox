<?php

/**
 * @file
 *
 * This file contains the default EntityGroup class.
 */

/**
 * Class EntityGroup
 */
class EntityGroup {
  use EntityToolboxCommonTraits;

  /**
   * @var string $name
   *   The group name.
   */
  protected $name;
  /**
   * @var array $info
   *   The group info.
   *
   * @see hook_entity_group_info().
   */
  protected $info = array();
  /**
   * @var string $label
   *   The group label.
   */
  protected $label;
  /**
   * @var string $rootPath
   *   The root path to access all the group's entities.
   */
  protected $rootPath;
  /**
   * @var array $hierarchy
   *   An array whose keys are entity types and the values are their weight in the group's hierarchy.
   */
  protected $hierarchy = array();
  /**
   * @var string[] $entityTypes
   *   An array containing the entity types attached to the group.
   */
  protected $entityTypes = array();
  /**
   * @var string[] $fieldableEntityTypes
   *   An array containing the entity types attached to the group.
   */
  protected $fieldableEntityTypes = array();
  /**
   * @var string[] $nonFieldableEntityTypes
   *   An array containing the entity types attached to the group.
   */
  protected $nonFieldableEntityTypes = array();
  /**
   * @var \EntityToolbox[] $entities
   *   The group's loaded entities.
   */
  protected $entities = array();
  /**
   * @var \EntityToolbox[] $tree
   *   An array containing the group entities sorted by hierarchy level.
   */
  protected $tree = array();
  /**
   * @var array $groupSettings
   *   The group's settings.
   */
  protected $groupSettings = array();
  /**
   * @var array $fieldGroups
   *   The group's fields groups.
   */
  protected $fieldGroups = array();
  /**
   * @var array $fieldCategories
   *   The group's field categories.
   */
  protected $fieldCategories = array();

  /**
   * EntityGroup constructor.
   *
   * @param string $name
   *   The group's name.
   * @param array  $args
   *   The args to set.
   */
  public function __construct($name, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'name' => $name
    ), $args);
    $this->setUp($args);
  }

  /**
   * @param array $args
   */
  protected function setUp(array $args = array()) {
    $this->setConstructArgs($args);
    foreach ($args as $argName => $arg) {
      $this->__set($argName, $arg);
    }
  }

  /**
   * @return string
   */
  public function getName() {
    return $this->name;
  }

  /**
   * @param string $name
   */
  public function setName($name) {
    $this->name = $name;
  }

  protected function postSetName() {
    $this->__set('info', entity_toolbox_entity_group_get_info($this->name));
  }

  /**
   * @return array
   */
  public function getInfo() {
    return $this->info;
  }

  /**
   * @param array $info
   */
  public function setInfo($info) {
    $this->info = $info;
  }

  /**
   * After info has been set.
   */
  protected function postSetInfo() {
    $this->__set('label', $this->info['label']);
    $this->__set('root_path', $this->info['path']);
    $this->__set('entity_types', $this->info['entity_types']);
    $controller = entity_group_get_controller($this->name);
    $this->__set('fieldable_entity_types', $controller->extractFieldableEntityTypes($this));
    $this->__set('fieldable_entity_types', $controller->extractNonFieldableEntityTypes($this));
    $this->__set('hierarchy', $controller->buildHierarchy($this));
    $this->__set('entities', $controller->loadEntities($this));
  }

  /**
   * @return string
   */
  public function getLabel() {
    return $this->label;
  }

  /**
   * @param string $label
   */
  public function setLabel($label) {
    $this->label = $label;
  }

  /**
   * @return string
   */
  public function getRootPath() {
    return $this->rootPath;
  }

  /**
   * @param string $rootPath
   */
  public function setRootPath($rootPath) {
    $this->rootPath = $rootPath;
  }

  /**
   * @return array
   */
  public function getHierarchy() {
    return $this->hierarchy;
  }

  /**
   * @param array $hierarchy
   */
  public function setHierarchy($hierarchy) {
    $this->hierarchy = $hierarchy;
  }

  /**
   * @return string[]
   */
  public function getEntityTypes() {
    return $this->entityTypes;
  }

  /**
   * @param string[] $entityTypes
   */
  public function setEntityTypes($entityTypes) {
    $this->entityTypes = $entityTypes;
  }

  /**
   * @return string[]
   */
  public function getFieldableEntityTypes() {
    return $this->fieldableEntityTypes;
  }

  /**
   * @param string[] $fieldableEntityTypes
   */
  public function setFieldableEntityTypes($fieldableEntityTypes) {
    $this->fieldableEntityTypes = $fieldableEntityTypes;
  }

  /**
   * @return string[]
   */
  public function getNonFieldableEntityTypes() {
    return $this->nonFieldableEntityTypes;
  }

  /**
   * @param string[] $nonFieldableEntityTypes
   */
  public function setNonFieldableEntityTypes($nonFieldableEntityTypes) {
    $this->nonFieldableEntityTypes = $nonFieldableEntityTypes;
  }

  /**
   * @return EntityToolbox[]
   */
  public function getEntities() {
    return $this->entities;
  }

  /**
   * @param EntityToolbox[] $entities
   */
  public function setEntities($entities) {
    $this->entities = $entities;
  }

  /**
   * @return EntityToolbox[]
   */
  public function getTree() {
    return $this->tree;
  }

  /**
   * @param EntityToolbox[] $tree
   */
  public function setTree($tree) {
    $this->tree = $tree;
  }

  /**
   * @return array
   */
  public function getGroupSettings() {
    return $this->groupSettings;
  }

  /**
   * @param array $groupSettings
   */
  public function setGroupSettings($groupSettings) {
    $this->groupSettings = $groupSettings;
  }

  /**
   * @return array
   */
  public function getFieldGroups() {
    return $this->fieldGroups;
  }

  /**
   * @param array $fieldGroups
   */
  public function setFieldGroups($fieldGroups) {
    $this->fieldGroups = $fieldGroups;
  }

  /**
   * @return array
   */
  public function getFieldCategories() {
    return $this->fieldCategories;
  }

  /**
   * @param array $fieldCategories
   */
  public function setFieldCategories($fieldCategories) {
    $this->fieldCategories = $fieldCategories;
  }
}