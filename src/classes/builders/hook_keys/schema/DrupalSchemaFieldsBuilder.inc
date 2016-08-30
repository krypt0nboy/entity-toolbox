<?php

/**
 * Class DrupalSchemaFieldsBuilder
 */
class DrupalSchemaFieldsBuilder extends SchemaKeyBuilder {
  /**
   * @var array $properties
   */
  protected $properties = array();

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $this->mergeConstructArgs(array(
      'self_key' => 'fields'
    ), $args);
    parent::__construct($args);
    $this->prepareStructure();
  }

  /**
   *
   */
  protected function prepareStructure() {
    $fields             = array();
    $structure          = array();
    $keyBuildersClasses = array();
    $keyBuildersArgs    = array();
    $this->properties   = $this->toolboxInfo['properties'];
    foreach ($this->properties as $property => $info) {
      if (!$info['multiple'] || $info['serialize']) {
        $fieldName          = $info['schemas_fields_name'][$this->schemaType];
        $fields[$fieldName] = array(
          'field_name'        => $fieldName,
          'property_name'     => $property,
          'key_builder_class' => 'DrupalSchemaFieldBuilder',
        );
      }
    }
    foreach ($fields as $fieldName => $fieldArgs) {
      $structure[$fieldName]          = array(
        'type'   => 'array',
        'method' => 'buildField'
      );
      $keyBuildersClasses[$fieldName] = $fieldArgs['key_builder_class'];
      $keyBuildersArgs[$fieldName]    = array(
        'field_name'    => $fieldName,
        'property_name' => $fieldArgs['property_name'],
      );
    }
    $this->__set('structure', $structure);
    $this->setKeyBuildersClasses($keyBuildersClasses);
    foreach ($this->getKeyBuildersClasses() as $fieldName => $keyBuildersClass) {
      $this->setKeyBuilder($fieldName, $this->keyBuilderGetInstance($keyBuildersClass, $keyBuildersArgs[$fieldName]));
    }
  }

  /**
   * @return array
   */
  public function getProperties() {
    return $this->properties;
  }

  /**
   * @param array $properties
   */
  public function setProperties($properties) {
    $this->properties = $properties;
  }

  /** {{@inheritdoc}} */
  public function build() {
    $build = array();
    foreach (array_keys($this->getStructure()) as $fieldName) {
      $build[$fieldName] = $this->buildField($fieldName);
    }
    if ($this->toolboxInfo['has_revisions']) {
      $build += $this->buildRevisionField();
    }
    if ($this->toolboxInfo['has_translations']) {
      $build += $this->buildTranslationSetField();
    }

    return $build;
  }

  /**
   * @param $fieldName
   * @return array
   */
  protected function buildField($fieldName) {
    return $this->getKeyBuilder($fieldName)->build();
  }

  /**
   * @return array
   */
  protected function buildRevisionField() {
    return array(
      'vid' => array(
        'type'        => 'int',
        'description' => $this->processValueTemplate('The current {%toolbox_info_tables_revision%}.%toolbox_info_keys_id% version identifier.'),
        'unsigned'    => TRUE,
        'not null'    => TRUE,
        'default'     => 0,
      )
    );
  }

  /**
   * @return array
   */
  protected function buildTranslationSetField() {
    $fieldName = $this->processValueTemplate('t%toolbox_info_entity_type%id');

    return array(
      $fieldName => array(
        'description' => $this->processValueTemplate('The translation set id for this %toolbox_info_entity_type%, which equals the %toolbox_info_entity_type% id in each set.'),
        'type'        => 'int',
        'unsigned'    => TRUE,
        'not null'    => TRUE,
        'default'     => 0,
      )
    );
  }

}