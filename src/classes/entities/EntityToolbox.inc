<?php

/**
 * @file
 *
 * This file contains entity_toolbox entity classes.
 */

/**
 * Class EntityToolbox
 */
class EntityToolbox extends Entity {

  /**
   * Toolbox info retrieved and processed by entity toolbox.
   *
   * @see hook_entity_toolbox_entity_info().
   * @see entity_toolbox_entity_get_info().
   */
  protected $toolboxInfo;

  /**
   * @var string $entityGroup
   *   The entity group.
   *
   * @see hook_entity_group_attach_info().
   */
  protected $entityGroup;

  /**
   * Constructor.
   *
   * @param array $values
   *   Values.
   * @param       $entity_type
   *   The entity type.
   *
   * @throws \Exception
   */
  public function __construct($values = array(), $entity_type = NULL) {
	parent::__construct($values, $entity_type);
  }

  /**
   * {@inheritdoc}
   */
  public function setUp() {
	parent::setUp();
	$this->toolboxInfo = entity_toolbox_entity_get_info($this->entityType);
	$this->entityGroup = $this->toolboxInfo['group'];
  }

  /**
   * Returns the entity toolbox info.
   *
   * @return array
   */
  public function toolboxInfo() {
	return $this->toolboxInfo;
  }

  /**
   * Returns the entity group.
   *
   * @return string
   */
  public function entityGroup() {
	return $this->entityGroup;
  }

  /**
   * Return the entity label.
   *
   * @return string
   *   Label.
   */
  protected function defaultLabel() {
	return parent::defaultLabel();
  }

  /**
   * Return the entity URI.
   *
   * @return array
   *   Uri.
   */
  protected function defaultUri() {
	//TODO : add entity uri template
	return array('path' => "$this->entityType/" . $this->idKey);
  }
}

/**
 * Class EntityToolboxFieldable
 */
class EntityToolboxFieldable extends EntityToolbox {

}

/**
 * Class EntityToolboxNotFieldable
 */
class EntityToolboxNotFieldable extends EntityToolbox {

}