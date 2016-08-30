<?php

/**
 * Class SchemaValueBuilder
 */
class DrupalSchemaBuilder extends SchemaKeyBuilder {

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'model_class'          => 'DrupalSchemaModel',
      'key_builders_classes' => array(
        'fields' => 'DrupalSchemaFieldsBuilder'
      ),
    ), $args);
    parent::__construct($args);
  }

  /**
   * Builds the description.
   *
   * @return string
   */
  protected function buildDescription() {
  }

  /**
   * Builds the fields.
   *
   * @return array
   */
  protected function buildFields() {
    $build = $this->getKeyBuilder('fields')->build();

    return $build;
  }

  /**
   * Builds the table indexes.
   *
   * @return array
   */
  protected function buildIndexes() {
  }

  /**
   * Builds the table primary key.
   *
   * @return array
   */
  protected function buildPrimaryKey() {
    $idProperty = $this->toolboxInfo['properties'][$this->toolboxInfo['keys']['id']];
    $field      = $idProperty['schemas_fields_name'][$this->schemaType];

    return array($field);
  }

  /**
   * Builds the unique key.
   *
   * @return array
   */
  protected function buildUniqueKeys() {
    $uniqueKeys = array();
    foreach ($this->toolboxInfo['properties'] as $property => $info) {
      if ($info['is_unique'] && !empty($info['schemas_fields_name'][$this->schemaType])) {
        $fieldName              = $info['schemas_fields_name'][$this->schemaType];
        $uniqueKeys[$fieldName] = array(
          array($fieldName)
        );
      }
    }

    return $uniqueKeys;
  }

  /**
   * Builds the foreign keys.
   *
   * @return array
   */
  protected function buildForeignKeys() {

  }

  /**
   * Adds a revision field.
   *
   */
  protected function addRevisionField() {
    
  }
}