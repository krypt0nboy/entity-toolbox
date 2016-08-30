<?php

/**
 * The Controller for entities managed by entity toolbox
 *
 * Class EntityToolboxEntityController
 */
class EntityToolboxController extends EntityAPIController {

  /**
   * Toolbox info retrieved and processed by entity toolbox.
   *
   * @see hook_entity_toolbox_entity_info().
   * @see entity_toolbox_get_info().
   */
  protected $toolboxInfo;
  /**
   * @var array $cacheInfo
   *   Entity cache info retrieved by entity toolbox.
   */
  protected $cacheInfo;
  /**
   * @var string $entityGroup
   *   The entity group.
   */
  protected $entityGroup;
  /**
   * @var string[] $inheritableProperties
   *   An array of properties to be inherited by children entities.
   */
  protected $inheritableProperties;
  /**
   * @var array $inheritedProperties
   *   An associative array whose keys are the properties to inherit from parent
   *   entities, and the values the parent(s) from which to inherit the property.
   */
  protected $inheritedProperties;
  /**
   * @var string[] $bundles
   *   The entity type bundles.
   */
  protected $bundles;

  /**
   * Constructor.
   *
   * @param string $entity_type
   *   Entity type.
   */
  public function __construct($entity_type) {
    parent::__construct($entity_type);
    $this->toolboxInfo = entity_toolbox_get_info($this->entityType);
    $this->setInheritableProperties();
    $this->setInheritedProperties();
  }

  /**
   * Return the entity toolbox info.
   *
   * @return array
   */
  public function toolboxInfo() {
    return $this->toolboxInfo;
  }

  /**
   * Returns the entity type revision key.
   */
  public function revisionKey() {
    return $this->entityInfo['keys']['revision'];
  }

  /**
   * Returns the author key.
   *
   * @return string
   */
  public function authorKey() {
    return $this->toolboxInfo['author_key'];
  }

  /**
   * Returns the entity author.
   *
   * @param \EntityToolbox $entity
   *   The entity.
   *
   * @return \Entity
   */
  public function author($entity) {
    return user_load($entity->{$this->authorKey()});
  }

  /**
   * Returns the entity author uid.
   *
   * @param \EntityToolbox $entity
   *   The entity.
   *
   * @return int
   */
  public function authorUid($entity) {
    return $entity->{$this->authorKey()};
  }

  /**
   * Retrieves the entity type existing bundles name.
   */
  protected function setBundles() {
    foreach ($this->types() as $key => $value) {
      $this->bundles[] = $key;
    }
  }

  /**
   * Returns the entity type bundle names.
   *
   * @return \string[]
   */
  public function bundles() {
    return $this->bundles;
  }

  /**
   * Returns a bundle entity.
   *
   * @param null|string $type
   *   The bundle name, or NULL to return every bundle.
   *
   * @return \NotFieldableEntityToolbox[]
   */
  public function types($type = NULL) {
    return entity_load_multiple_by_name($this->toolboxInfo['bundle_entity'], isset($type) ? array($type) : FALSE);
  }

  /**
   * Retrieves the inheritable properties.
   */
  protected function setInheritableProperties() {
    $this->inheritableProperties = entity_toolbox_inheritable_property_get_info($this->entityType);
  }

  /**
   * Returns inheritable properties.
   *
   * @return string[]
   */
  public function inheritableProperties() {
    return $this->inheritableProperties;
  }

  /**
   * Retrieves the entity type inherited properties.
   */
  protected function setInheritedProperties() {
    $this->inheritedProperties = entity_toolbox_inherited_property_get_info($this->entityType);
  }

  /**
   * Returns the inherited properties.
   *
   * @return array
   */
  public function inheritedProperties() {
    return $this->inheritedProperties;
  }

  /**
   * Returns a property relation table.
   *
   * @param string $name
   *   The property name.
   *
   * @return string
   */
  public function propertyRelationTable($name) {
    $property = $this->toolboxInfo['properties'][$name];

    return key($property['schemas']['relation']['name']);
  }

  /**
   * Returns a property relation table.
   *
   * @param string $name
   *   The property name.
   *
   * @return string
   */
  public function propertyRelationTableField($name) {
    $property = $this->toolboxInfo['properties'][$name];

    return $property['schemas_fields']['relation'];
  }

  /**
   * Returns the parameters of a relation table between two entity types.
   *
   * @param \EntityToolbox $entity
   *   The entity.
   * @param string         $name
   *   The property name.
   *
   * @return array
   */
  public function relationExtractInfo($entity, $name) {
    return array(
      'self_id_key' => $this->idKey,
      'self_id'     => $entity->{$this->idKey},
      'rel_table'   => $this->propertyRelationTable($name),
      'ref_rel_key' => $this->propertyRelationTableField($name),
    );
  }

  /**
   * Inserts values for a multi value reference property.
   *
   * @param \EntityToolbox $entity
   *   The entity.
   * @param string         $name
   *   The property name.
   * @param int[]          $add_ids
   *   A list of numeric ids to insert as values.
   *
   * @return array
   * @throws \Exception
   */
  public function insertMultiReferenceValues($entity, $name, $add_ids = array()) {
    list($self_id_key, $self_id, $rel_table, $ref_rel_key) = $this->relationExtractInfo($entity, $name);
    $inserted = array();
    foreach ($add_ids as $add_id) {
      $inserted[] = db_insert($rel_table)
        ->fields(
          array(
            $self_id_key => $self_id,
            $ref_rel_key => $add_id
          )
        )
        ->execute();
    }

    return $inserted;
  }

  /**
   * Deletes values of a multi value reference property.
   *
   * @param \EntityToolbox $entity
   *   The entity.
   * @param string         $name
   *   The property name.
   * @param int[]          $del_ids
   *   The references to delete.
   */
  public function deleteMultiReferenceValues($entity, $name, $del_ids = array()) {
    list($self_id_key, $self_id, $rel_table, $ref_rel_key) = $this->relationExtractInfo($entity, $name);
    db_delete($rel_table)
      ->condition($self_id_key, $self_id)
      ->condition($ref_rel_key, $del_ids, 'IN')
      ->execute();
  }

  /**
   * Determines if the load has to be skipped.
   *
   * @param array $calls
   *   The called hook response.
   *
   * @return bool
   */
  public function requiresSkipLoad($calls) {

  }

  /**
   * Returns a property default value.
   *
   * @param string $name
   *   The property type.
   *
   * @return mixed
   */
  public function propertyDefaultValue($name) {
    $property = $this->toolboxInfo['properties'][$name];
    if (!empty($property['default'])) {
      return $property['default'];
    }
    else {
      $callback = $property['callbacks']['default'];

      return $callback($this->entityType);
    }
  }

  /**
   * Returns properties default values.
   *
   * @return array
   */
  public function propertiesDefaultValues() {
    $values = array();
    foreach ($this->toolboxInfo['properties'] as $name => $property) {
      $values[$property['key']] = $this->propertyDefaultValue($name);
    }

    return $values;
  }

  /**
   * Returns a boolean indicating if a property is a list of values.
   *
   * @param string $name
   *   The property name.
   *
   * @return bool
   */
  public function isPropertyMultiValue($name) {
    $property = $this->toolboxInfo['properties'][$name];

    return $property['multiple'];
  }

  /**
   * Validates an entity property.    $property    = $this->toolboxInfo['properties'][$name];
   *
   * @param \EntityToolbox $entity
   *   The entity.
   * @param string         $name
   *   The property name.
   * @param array          $form
   *   The entity form, passed by reference
   * @param array          $form_state
   *   The form state, passed by reference.
   */
  public function propertyValidate(&$entity, $name, &$form, &$form_state) {
    //@todo gather the property validation callbacks
    _property_validate($this->entityType, $entity, $name, $form, $form_state);
  }

  /**
   * Submits an entity property.
   *
   * @param \EntityToolbox $entity
   *   The entity.
   * @param string         $name
   *   The property name.
   * @param array          $form
   *   The entity form, passed by reference
   * @param array          $form_state
   *   The form state, passed by reference.
   */
  public function propertySubmit(&$entity, $name, &$form, &$form_state) {
    _property_submit($this->entityType, $entity, $name, $form, $form_state);
  }

  /**
   * Sets an entity multi value property.
   *
   * @param \EntityToolbox $entity
   *   The entity for which to set the value.
   * @param string         $name
   *   The property name.
   * @param array          $values
   *   The values to set.
   * @param null|string    $langcode
   *   The language code.
   * @param array          $options
   *   The set options.
   */
  public function setMultiValueProperty($entity, $name, $values, $langcode = NULL, $options = array()) {
    //@todo handle serialized multi value.
    //@todo handle non referential multi value.
    //@todo add hook_property_pre_set
    //@todo add hook_property_post_set
  }

  /**
   * Sets an entity multi value property.
   *
   * @param \EntityToolbox $entity
   *   The entity for which to set the value.
   * @param string         $name
   *   The property name.
   * @param array          $values
   *   The values to set.
   * @param null|string    $langcode
   *   The language code.
   * @param array          $options
   *   The set options.
   */
  public function setMultiValueReferenceProperty($entity, $name, $values = array(), $langcode = NULL, $options = array()) {
    //@todo add hook_property_pre_set
    //@todo add hook_property_post_set
    $values  = is_array($values) ? $values : array();
    $cur_ids = $this->getMultiValueProperty($entity, $name, NULL, $langcode, $options);
    $del_ids = array_diff($cur_ids, $values);
    $add_ids = array_diff($values, $cur_ids);

    if (!empty($add_ids)) {
      $this->insertMultiReferenceValues($entity, $name, $add_ids);
    }
    if (!empty($del_ids)) {
      $this->deleteMultiReferenceValues($entity, $name, $del_ids);
    }
  }

  /**
   * Gets an entity multi value property.
   *
   * @param \EntityToolbox $entity
   *   The entity for which to set the value.
   * @param string         $name
   *   The property name.
   * @param int            $delta
   *   The values to set.
   * @param null|string    $langcode
   *   The language code.
   * @param array          $options
   *   The get options.
   *
   * @return array
   */
  public function getMultiValueProperty($entity, $name, $delta = NULL, $langcode = NULL, $options = array()) {
    $property = $this->toolboxInfo['properties'][$name];
    if ($property['type'] == 'reference' || $property['type'] == 'parent') {
      return isset($delta) ? $this->getMultiValueReferenceProperty($entity, $name, $delta, $langcode, $options)[$delta] : $this->getMultiValueReferenceProperty($entity, $name, $delta, $langcode, $options);
    }
    else {
      //@todo handle serialized multi values
      return array();
    }
  }

  /**
   * Gets an entity multi value reference property.
   *
   * @param \EntityToolbox $entity
   *   The entity for which to set the value.
   * @param string         $name
   *   The property name.
   * @param int            $delta
   *   The values to set.
   * @param null|string    $langcode
   *   The language code.
   * @param array          $options
   *   The get options.
   *
   * @return \Entity[]
   */
  public function getMultiValueReferenceProperty($entity, $name, $delta = NULL, $langcode = NULL, $options = array()) {
    list($self_id_key, $self_id, $rel_table, $ref_rel_key) = $this->relationExtractInfo($entity, $name);
    $query   = db_select($rel_table, 'e')
      ->fields('e', array())
      ->condition('e.' . $self_id_key, $self_id)
      ->execute();
    $results = array();
    while ($result = $query->fetchAssoc()) {
      $results[] = $result[$ref_rel_key];
    }

    return $results;
  }

  /**
   * Create an entity.
   *
   * @param array $values
   *   The values of the entity.
   *
   * @return object
   *   An entity object with all default fields initialized.
   */
  public function create(array $values = array()) {
    $values += $this->propertiesDefaultValues();
    $entity = parent::create($values);

    return $entity;
  }

  /**
   * Overriding the buildContent function to add entity specific fields.
   *
   * @param object $entity
   *   Entity.
   * @param string $view_mode
   *   View mode.
   * @param string $langcode
   *   Language code.
   * @param array  $content
   *   Content.
   *
   * @return array
   *   The content built.
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $content = parent::buildContent($entity, $view_mode, $langcode, $content);

    return $content;
  }

  /**
   * Build breadcrumbs.
   */
  public function buildBreadCrumbs() {
  }

}